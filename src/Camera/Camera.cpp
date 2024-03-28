#include "Camera.h"

#include <iostream>

#include "Globals/Time.h"

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
    Zoom = ZOOM;
    previousTargetRotation = glm::vec3(0.0f);
    updateCameraVectors();
}

void Camera::checkKeywoardMovement(GLFWwindow* window)
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
    }
    Position.y = 0.0f;
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}

glm::mat4 Camera::getViewMatrix()
{
    return !thirdPerson ? glm::lookAt(Position, Position + Front, Up) : glm::lookAt(PositionThirdPerson, Target, Up);
}

glm::mat4 Camera::getProjectionMatrix(float width, float height)
{
    return glm::perspective(glm::radians(Zoom), width / height, NEAR_PLANE, FAR_PLANE);
}

void Camera::changeCameraObjetive(glm::vec3 target, glm::vec3 rotationEulerAngle)
{
    Target = target;
    thirdPerson = true;
    PositionThirdPerson = target + Front * 500.0f;

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
