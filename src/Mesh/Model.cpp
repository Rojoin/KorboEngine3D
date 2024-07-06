#include "Renderer/Frustrum.h"
#include "Model.h"


Model::Model(const char* path, Renderer* renderer, Vec3 position, Vec3 rotation, Vec3 newScale,
             bool shouldInvertUVs, Transform* parent): Entity3D(renderer, position, rotation, newScale)
{
    tranform->name = path;
    Importer3D::loadModel(path, directory, meshes, shouldInvertUVs, this);
    boundingVolume = make_unique<AABB>(generateAABB(*this));
    if (parent != nullptr)
    {
        tranform->parent = parent;
        parent->childs.push_back(this->tranform);
    }

}


Model::Model(Renderer* renderer, Transform* parent,Vec3 position, Vec3 rotation, Vec3 newScale) : Entity3D(renderer,position,rotation, newScale)
{
    boundingVolume = make_unique<AABB>(generateAABB(*this));
    tranform->parent = parent;
    parent->childs.push_back(this->tranform);
}


void Model::Draw()
{
    tranform->UpdateMatrix();
    for (int i = 0; i < meshes.size(); ++i)
    {
        renderer->DrawModel3D(this->tranform->modelWorld, meshes[i].VAO, meshes[i].indices, meshes[i].textures);
    }
    if (!tranform->childs.empty())
    {
        for (auto child : tranform->childs)
        {
            if (child->entity != nullptr)
            {
                child->entity->Draw();
            }
        }
    }
}

void Model::setNewTextures(string currentDirectory, string fileName, bool shouldInvertUVs, string type)
{
    for (BasicMesh& mesh : meshes)
    {
        mesh.setNewTextures(currentDirectory,fileName,shouldInvertUVs,type);
    }
    if (!tranform->childs.empty())
    {
        for (auto child : tranform->childs)
        {
            if (child->entity != nullptr && dynamic_cast<Model*>(child->entity))
            {
                dynamic_cast<Model*>(child->entity)->setNewTextures(currentDirectory,fileName,shouldInvertUVs,type);
            }
        }
    }
}

Model::~Model()
{
    std::cout << "Deleting model";
}

AABB Model::getGlobalAABB()
{
    //Get global scale thanks to our transform
    const glm::vec3 globalCenter{this->tranform->getLocalModelMatrix() * glm::vec4(boundingVolume->center, 1.f)};

    // Scaled orientation
    glm::vec3 right = this->tranform->getRight() * boundingVolume->extents.x;
    glm::vec3 up = this->tranform->getUp() * boundingVolume->extents.y;
    glm::vec3 forward = this->tranform->getForward() * boundingVolume->extents.z;

    const float newIi = std::abs(glm::dot(glm::vec3{1.f, 0.f, 0.f}, right)) +
        std::abs(glm::dot(glm::vec3{1.f, 0.f, 0.f}, up)) +
        std::abs(glm::dot(glm::vec3{1.f, 0.f, 0.f}, forward));

    const float newIj = std::abs(glm::dot(glm::vec3{0.f, 1.f, 0.f}, right)) +
        std::abs(glm::dot(glm::vec3{0.f, 1.f, 0.f}, up)) +
        std::abs(glm::dot(glm::vec3{0.f, 1.f, 0.f}, forward));

    const float newIk = std::abs(glm::dot(glm::vec3{0.f, 0.f, 1.f}, right)) +
        std::abs(glm::dot(glm::vec3{0.f, 0.f, 1.f}, up)) +
        std::abs(glm::dot(glm::vec3{0.f, 0.f, 1.f}, forward));

    return AABB(globalCenter, newIi, newIj, newIk);
}
