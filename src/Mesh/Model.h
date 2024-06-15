#pragma once
#include "BasicMesh.h"
#include "Importer3D.h"
#include "Shader/shader.h"
#include "assimp/mesh.h"
#include "Entity/Entity3D.h"

class EXPORT Model : public Entity3D
{
public:
    Model(const char* path, Renderer* renderer, Vec3 position, Vec3 rotation, Vec3 newScale,
          bool shouldInvertUVs = false);
    void draw(Shader* shader);
    ~Model() override;

private:
    // model data
    vector<BasicMesh> meshes;
    string directory;
};
