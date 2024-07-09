#include "BoundingVolumes.h"

#include "Mesh/Model.h"


bool BoundingVolume::isOnFrustum(const Frustum& camFrustum) 
{
    return (isOnOrForwardPlane(camFrustum.leftFace) &&
        isOnOrForwardPlane(camFrustum.rightFace) &&
        isOnOrForwardPlane(camFrustum.topFace) &&
        isOnOrForwardPlane(camFrustum.bottomFace) &&
        isOnOrForwardPlane(camFrustum.nearFace) &&
        isOnOrForwardPlane(camFrustum.farFace));
}

SquareAABB::SquareAABB(const glm::vec3& inCenter, float inExtent): BoundingVolume{}, center{ inCenter }, extent{ inExtent }
{}

bool SquareAABB::isOnOrForwardPlane(const Plane& plane) const
{
    // Compute the projection interval radius of b onto L(t) = b.c + t * p.n
    const float r = extent * (std::abs(plane.normal.x) + std::abs(plane.normal.y) + std::abs(plane.normal.z));
    return -r <= plane.getSignedDistanceToPlane(center);
}

bool SquareAABB::isOnFrustum(const Frustum camFrustum, const Transform* transform) const
 {
     //Get global scale thanks to our transform
     const glm::vec3 globalCenter{ transform->getLocalModelMatrixConst() * glm::vec4(center, 1.f) };

     // Scaled orientation
     const glm::vec3 right = transform->getRightConst() * extent;
     const glm::vec3 up = transform->getUpConst() * extent;
     const glm::vec3 forward = transform->getForwardConst() * extent;

     const float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
         std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
         std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));

     const float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
         std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
         std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));

     const float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
         std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
         std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));

      SquareAABB globalAABB(globalCenter, std::max(std::max(newIi, newIj), newIk));

     return (globalAABB.isOnOrForwardPlane(camFrustum.leftFace) &&
         globalAABB.isOnOrForwardPlane(camFrustum.rightFace) &&
         globalAABB.isOnOrForwardPlane(camFrustum.topFace) &&
         globalAABB.isOnOrForwardPlane(camFrustum.bottomFace) &&
         globalAABB.isOnOrForwardPlane(camFrustum.nearFace) &&
         globalAABB.isOnOrForwardPlane(camFrustum.farFace));
 }


AABB::~AABB()
{
}

 std::vector<glm::vec3>  AABB::getVertice() const
{
    std::vector<glm::vec3> vertice(8);
    vertice[0] = center + glm::vec3(-extents.x, -extents.y, -extents.z);
    vertice[1] = center + glm::vec3(extents.x, -extents.y, -extents.z);
    vertice[2] = center + glm::vec3(extents.x, extents.y, -extents.z);
    vertice[3] = center + glm::vec3(-extents.x, extents.y, -extents.z);
    vertice[4] = center + glm::vec3(-extents.x, -extents.y, extents.z);
    vertice[5] = center + glm::vec3(extents.x, -extents.y, extents.z);
    vertice[6] = center + glm::vec3(extents.x, extents.y, extents.z);
    vertice[7] = center + glm::vec3(-extents.x, extents.y, extents.z);
    return vertice;
}

bool AABB::isOnOrForwardPlane(const Plane& plane) const
{
    // Compute the projection interval radius of b onto L(t) = b.c + t * p.n
    const float r = extents.x * std::abs(plane.normal.x) + extents.y * std::abs(plane.normal.y) +
        extents.z * std::abs(plane.normal.z);

    return -r <= plane.getSignedDistanceToPlane(center);
}

bool AABB::isOnFrustum(const Frustum camFrustum, const Transform* transform) const 
{
    //Get global scale thanks to our transform
    const glm::vec3 globalCenter{ transform->modelWorld * glm::vec4(center, 1.f) };

    // Scaled orientation
    const glm::vec3 right = transform->getRightConst() * extents;
    const glm::vec3 up = transform->getUpConst() * extents;
    const glm::vec3 forward = transform->getForwardConst() * extents;

    const float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
        std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
        std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));

    const float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
        std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
        std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));

    const float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
        std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
        std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));

     AABB globalAABB(globalCenter, newIi, newIj, newIk);

    return (globalAABB.isOnOrForwardPlane(camFrustum.leftFace) &&
        globalAABB.isOnOrForwardPlane(camFrustum.rightFace) &&
        globalAABB.isOnOrForwardPlane(camFrustum.topFace) &&
        globalAABB.isOnOrForwardPlane(camFrustum.bottomFace) &&
        globalAABB.isOnOrForwardPlane(camFrustum.nearFace) &&
        globalAABB.isOnOrForwardPlane(camFrustum.farFace));
}

AABB AABB::generateAABB(const Model& model)
{
    glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
    glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());
    for (const BasicMesh& mesh : model.meshes)
    {
        for (const Vertex& vertex : mesh.vertices)
        {
            minAABB.x = std::min(minAABB.x, vertex.Position.x);
            minAABB.y = std::min(minAABB.y, vertex.Position.y);
            minAABB.z = std::min(minAABB.z, vertex.Position.z);

            maxAABB.x = std::max(maxAABB.x, vertex.Position.x);
            maxAABB.y = std::max(maxAABB.y, vertex.Position.y);
            maxAABB.z = std::max(maxAABB.z, vertex.Position.z);
        }
    }

    return AABB(minAABB, maxAABB);
}
