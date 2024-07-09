#include "Camera.h"

#include <iostream>

#include "Globals/Time.h"
#include <GLFW/glfw3.h>
#include  "Entity/Transform.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch): Front(glm::vec3(0.0f, 0.0f, -1.0f)),
                                                                          MovementSpeed(SPEED),
                                                                          MouseSensitivityX(SENSITIVITY_X),
                                                                          MouseSensitivityY(SENSITIVITY_Y), Zoom(ZOOM)
{
    Position = position;
    PositionThirdPerson = glm::vec3(Position.x, Position.y + 2.0f,
                                    Position.z - 5.0f);
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    firstMouse = true;
    thirdPerson = false;
    Zoom = ZOOM;
    previousTargetRotation = glm::vec3(0.0f);
    this->transform = new Transform(nullptr, position, glm::vec3(pitch,yaw,0), glm::vec3(1));
    updateCameraVectors();
}

Camera::~Camera()
{
    delete transform;
}

void Camera::checkKeyboardMovement(GLFWwindow* window)
{
    float currentTime = Time::getDeltaTime();

    MovementSpeedBonus = 1.0f;
    if (!thirdPerson)
    {
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            MovementSpeedBonus = SPEED_BONUS;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            Position += MovementSpeed * MovementSpeedBonus * Front * currentTime;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            Position -= MovementSpeed * MovementSpeedBonus * Front * currentTime;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            Position -= glm::normalize(glm::cross(Front, Up)) * MovementSpeedBonus * MovementSpeed * currentTime;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            Position += glm::normalize(glm::cross(Front, Up)) * MovementSpeedBonus * MovementSpeed * currentTime;
        }
        Position.y = 0.0f;
        transform->setLocalPosition(Position);
    }

    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    Front = transform->getForward();
    Right = transform->getRight();
    Up = transform->getUp();
}

glm::mat4 Camera::getViewMatrix()
{
    return !thirdPerson
               ? glm::lookAt(transform->localPosition, transform->localPosition + transform->getForward(),
                             transform->getUp())
               : glm::lookAt(PositionThirdPerson, Target, transform->getUp());
}

glm::vec3 Camera::getCameraPosition()
{
    return thirdPerson ? PositionThirdPerson : transform->localPosition;
}

glm::mat4 Camera::getProjectionMatrix(float width, float height)
{
    return glm::perspective(glm::radians(Zoom), width / height, NEAR_PLANE, FAR_PLANE);
}

void Camera::changeCameraObjetive(glm::vec3 target, glm::vec3 rotationEulerAngle)
{
    if (!thirdPerson)
        return;
    Target = target;
    PositionThirdPerson = target + transform->getForward() * 500.0f;

    float newRotationY = previousTargetRotation.y - rotationEulerAngle.y;

    Yaw += newRotationY;
    previousTargetRotation = rotationEulerAngle;
    updateCameraVectors();
}

void Camera::checkMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivityX;
    yoffset *= MouseSensitivityY;


    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    transform->setLocalRotation({Pitch, -Yaw, 0});
    updateCameraVectors();
}

void Camera::checkMouseScroll(float yoffset)
{
    Zoom -= yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = ZOOM;
}

void Camera::toggleCameraMode()
{
    thirdPerson = !thirdPerson;

    if (thirdPerson)
    {
        PositionThirdPerson = glm::vec3(transform->getLocalPosition().x, transform->getLocalPosition().y + 2.0f,
                                        transform->getLocalPosition().z - 5.0f);
    }
    else
    {
        Position = glm::vec3(PositionThirdPerson.x, PositionThirdPerson.y - 2.0f, PositionThirdPerson.z + 5.0f);
        transform->setLocalPosition(Position);
    }
}
