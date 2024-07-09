#include <array>

#include "Frustrum.h"
#include "Entity/Transform.h"


class Model;


struct BoundingVolume
{
    virtual ~BoundingVolume() = default;
    virtual bool isOnFrustum(const Frustum camFrustum, const Transform* transform) const = 0;

    virtual bool isOnOrForwardPlane(const Plane& plane) const = 0;

    bool isOnFrustum(const Frustum& camFrustum);
};


struct SquareAABB : public BoundingVolume
{
    glm::vec3 center{0.f, 0.f, 0.f};
    float extent{0.f};

    SquareAABB(const glm::vec3& inCenter, float inExtent);

    bool isOnOrForwardPlane(const Plane& plane) const final;

    bool isOnFrustum(const Frustum camFrustum, const Transform* transform)const override;
};


struct AABB : public BoundingVolume
{
    glm::vec3 center{0.f, 0.f, 0.f};
    glm::vec3 extents{0.f, 0.f, 0.f};

    AABB(const glm::vec3& min, const glm::vec3& max): BoundingVolume{}, center{(max + min) * 0.5f},
                                                      extents{max.x - center.x, max.y - center.y, max.z - center.z}
    {
    }

    AABB(const glm::vec3& inCenter, float iI, float iJ, float iK): BoundingVolume{}, center{inCenter},
                                                                   extents{iI, iJ, iK}
    {
    }
~AABB() override;
   std::vector<glm::vec3>  getVertice() const;

    //see https://gdbooks.gitbooks.io/3dcollisions/content/Chapter2/static_aabb_plane.html
    bool isOnOrForwardPlane(const Plane& plane) const final;

    bool isOnFrustum(const Frustum camFrustum, const Transform* transform) const override;
static AABB generateAABB(const Model& model);
    
    std::string toString() const
    {
        std::ostringstream oss;
        oss << "Center:" << "X: " << center.x << ", Y: " << center.y << ", Z: " <<center.z << std::endl;
        oss << "Extends:" << "X: " << extents.x << ", Y: " << extents.y << ", Z: " <<extents.z;
        std::string result = oss.str();
        return result;
    }
};

