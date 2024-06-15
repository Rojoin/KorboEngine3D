#include "Model.h"

Model::Model(const char* path, Renderer* renderer, Vec3 position,Vec3 rotation, Vec3 newScale,bool shouldInvertUVs): Entity3D(renderer, position,rotation, newScale)
{
    Importer3D::loadModel(path, directory, meshes, shouldInvertUVs);
}


void Model::draw(Shader* shader)
{
    for (int i = 0; i < meshes.size(); ++i)
    {
       renderer->DrawModel3D(shader,this->tranform->model,meshes[i].VAO,meshes[i].indices,meshes[i].textures);
    }
}

Model::~Model()
{
}
