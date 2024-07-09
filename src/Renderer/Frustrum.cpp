#include "Frustrum.h"
#include "Camera/Camera.h"

Plane::Plane(const glm::vec3& p1, const glm::vec3& norm): normal(glm::normalize(norm)),
                                                          distance(glm::dot(normal, p1))
{
}

float Plane::getSignedDistanceToPlane(const glm::vec3& point) const
{
    return glm::dot(normal, point) - distance;
}

Frustum Frustum::createFrustumFromCamera(Camera* cam, float aspect, float fovY, float zNear, float zFar)
{
    Frustum frustum;
    const float halfVSide = zFar * tanf(fovY * 0.5f);
    const float halfHSide = halfVSide * aspect;
    const glm::vec3 frontMultFar = zFar * cam->Front;

    frustum.nearFace = {cam->Position + zNear * cam->Front, cam->Front};
    frustum.farFace = {cam->Position + frontMultFar, -cam->Front};

    const glm::vec3 rightPlaneNormal = glm::normalize(glm::cross(cam->Up, frontMultFar - cam->Right * halfHSide));
    frustum.rightFace = {cam->Position, rightPlaneNormal};

    const glm::vec3 leftPlaneNormal = glm::normalize(glm::cross(frontMultFar + cam->Right * halfHSide, cam->Up));
    frustum.leftFace = {cam->Position, leftPlaneNormal};

    const glm::vec3 topPlaneNormal = glm::normalize(glm::cross(frontMultFar - cam->Up * halfVSide, cam->Right));
    frustum.topFace = {cam->Position, topPlaneNormal};

    const glm::vec3 bottomPlaneNormal = glm::normalize(glm::cross(cam->Right, frontMultFar + cam->Up * halfVSide));
    frustum.bottomFace = {cam->Position, bottomPlaneNormal};
    return frustum;
}


