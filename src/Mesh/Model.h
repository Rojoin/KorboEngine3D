#pragma once
#include "BasicMesh.h"
#include "Importer3D.h"
#include "Shader/shader.h"
#include "assimp/mesh.h"
#include "Entity/Entity3D.h"
#include "Renderer/Frustrum.h"
#include "Renderer/TransReceiver.h"



struct AABB;
class EXPORT Model : public Entity3D
{
public:
    Model(const char* path, Renderer* renderer, Vec3 position, Vec3 rotation, Vec3 newScale,
          bool shouldInvertUVs = false, bool shouldBeTurnOffByBSP = false);
    Model(const char* path, Renderer* renderer, Vec3 position, Vec3 rotation, Vec3 newScale, bool shouldInvertUVs = false,
          Transform* parent = nullptr, bool shouldBeTurnOffByBSP = false);
    Model(Renderer* renderer, Transform* parent, Vec3 position, Vec3 rotation, Vec3 newScale, bool shouldBeTurnOffByBSP = false);
    void Draw() override;
    bool isOnFrustum(Frustum frustum);
    bool DrawWithFrustum(Frustum frustum, bool shouldBeDrawn);
    bool DrawWithBSP(std::vector<Plane>& bspPlanes, std::vector<bool>& cameraPlanes, Frustum frustum,
                     bool shouldBeDrawn);
    void setNewTextures(string currentDirectory, string fileName, bool shouldInvertUVs, string type);
   unique_ptr<AABB> boundingVolume;
    void recursiveAABB(glm::vec3& minAABB, glm::vec3& maxAABB,const glm::mat4& parentTransformMatrix);
   void setMinMaxBoundingVolume(glm::vec3& minAABB, glm::vec3& maxAABB,const glm::mat4& transformMatrix);
    ~Model() override;
    void generateAABB();
    vector<BasicMesh> meshes;
  AABB getGlobalAABB();
    //void drawBoundingBox(AABB* aabb, Shader* shaderProgram);

private:
    // model data
    string directory;
   // TransReceiver receiver;
};


