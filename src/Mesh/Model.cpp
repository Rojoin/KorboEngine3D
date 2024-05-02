#include "Model.h"

Model::Model(const char* path, Renderer* renderer, Vec3 position, Vec3 newScale): Entity3D(renderer, position, newScale)
{
    Importer3D::loadModel(path, directory, meshes);
}


void Model::draw(Shader* shader)
{
    for (int i = 0; i < meshes.size(); ++i)
    {
        renderer->DrawModel3D(shader,model,meshes[i].VAO,meshes[i].indices,meshes[i].textures);
    }
}
