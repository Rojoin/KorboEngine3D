#include "Camera.h"



#include "Globals/Time.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch): Front(glm::vec3(0.0f, 0.0f, -1.0f)),
                                                                          MovementSpeed(SPEED),
                                                                          MouseSensitivityX(SENSITIVITY_X),
                                                                          MouseSensitivityY(SENSITIVITY_Y), Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

void Camera::checkKeywoardMovement(GLFWwindow* window)
{
    float currentTime = Time::getDeltaTime();
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Position += MovementSpeed * Front * currentTime;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Position -= MovementSpeed * Front * currentTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Position -= glm::normalize(glm::cross(Front, Up)) * MovementSpeed * currentTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Position += glm::normalize(glm::cross(Front, Up)) * MovementSpeed * currentTime;
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
    return glm::lookAt(Position, Position + Front, Up);
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
