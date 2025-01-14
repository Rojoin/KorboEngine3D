﻿#pragma once


#include <glm/gtc/matrix_transform.hpp>
#include "Globals/dllHeader.h"

class Transform;
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 100.5f;
const float SPEED_BONUS = 2.0f;
const float SENSITIVITY_X = 0.2f;
const float SENSITIVITY_Y = 0.1f;
const float ZOOM = 45.0f;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 2000.0f;

struct GLFWwindow ;
typedef unsigned char GLboolean;
class EXPORT Camera
{
public:
    Transform* transform;
    glm::vec3 Position;
    glm::vec3 Target;
    glm::vec3 PositionThirdPerson;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MovementSpeedBonus;
    float MouseSensitivityX;
    float MouseSensitivityY;
    float Zoom;

    float lastX;
    float lastY;
    bool firstMouse = true;
    bool thirdPerson = false;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW, float pitch = PITCH);
    ~Camera();
    void checkKeyboardMovement(GLFWwindow* window);
    glm::mat4 getViewMatrix();
    glm::vec3 getCameraPosition();
    glm::mat4 getProjectionMatrix(float width, float height);
    void changeCameraObjetive(glm::vec3 target, glm::vec3 rotationEulerAngle);
    void checkMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void checkMouseScroll(float yoffset);
    void toggleCameraMode();

private:
    void updateCameraVectors();
    glm::vec3 previousTargetRotation;
};
