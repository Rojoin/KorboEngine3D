#pragma once
#include "BasicMesh.h"
#include "Importer3D.h"
#include "Shader/shader.h"
#include "assimp/mesh.h"
#include "Entity/Entity3D.h"

struct AABB;

class EXPORT Model : public Entity3D
{
public:
    Model(const char* path, Renderer* renderer, Vec3 position, Vec3 rotation, Vec3 newScale,
          bool shouldInvertUVs = false);
    Model(Renderer* renderer, Transform* parent);
    void Draw() override;
    void setNewTextures(string currentDirectory, string fileName, bool shouldInvertUVs, string type);
    unique_ptr<AABB> boundingVolume;
    ~Model() override;
    vector<BasicMesh> meshes;
    AABB getGlobalAABB();

private:
    // model data
    string directory;
};
