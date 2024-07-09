#include "Frustrum.h"
#include "Camera/Camera.h"
#include "Entity/Transform.h"

Plane::Plane(const glm::vec3& p1, const glm::vec3& norm): normal(glm::normalize(norm)),
                                                          distance(glm::dot(normal, p1))
{
}

void Plane::setNormalAndDistance(glm::vec3 point, glm::vec3 normal)
{
    this->normal = glm::normalize(normal);
    distance = glm::dot(this->normal, point);
}

float Plane::getSignedDistanceToPlane(const glm::vec3& point) const
{
    return glm::dot(normal, point) - distance;
}

void Frustum::createFrustumFromCamera(Camera* cam, float aspect, float fovY, float zNear, float zFar)
{
    glm::vec3 camUp = cam->Up;
    glm::vec3 camRight = cam->Right;
    glm::vec3 camForward = cam->Front;
    glm::vec3 camPos = (cam->transform->getLocalPositionGLM());
    float halfheight = zFar * (glm::tan((fovY * .5f) * glm::pi<float>() / 180.f));
    float halfWidth = halfheight * aspect;
    glm::vec3 frontFar = zFar * camForward;

    nearFace.setNormalAndDistance(camPos + zNear * camForward, camForward);
    farFace.setNormalAndDistance(camPos + frontFar, -camForward);

    rightFace.setNormalAndDistance(camPos, glm::cross(camUp, frontFar + camRight * halfWidth));
    leftFace.setNormalAndDistance(camPos, glm::cross(frontFar - camRight * halfWidth, camUp));
    topFace.setNormalAndDistance(camPos, glm::cross(camRight, frontFar - camUp * halfheight));
    bottomFace.setNormalAndDistance(camPos, glm::cross(frontFar + camUp * halfheight, camRight));
}
