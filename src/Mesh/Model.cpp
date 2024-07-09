#include "Model.h"

#include "BasicMesh.h"
#include "Renderer/TransSource.h"
#include "Renderer/BoundingVolumes.h"


Model::Model(const char* path, Renderer* renderer, Vec3 position, Vec3 rotation, Vec3 newScale,
             bool shouldInvertUVs, Transform* parent): Entity3D(renderer, position, rotation, newScale)
{
    tranform->name = path;
    Importer3D::loadModel(path, directory, meshes, shouldInvertUVs, this);
    boundingVolume = make_unique<AABB>(AABB::generateAABB(*this));

    // receiver.hookEvent(tranform->updateAABB);
    if (parent != nullptr)
    {
        tranform->parent = parent;
        parent->childs.push_back(this->tranform);
    }
}


Model::Model(Renderer* renderer, Transform* parent, Vec3 position, Vec3 rotation, Vec3 newScale) : Entity3D(
    renderer, position, rotation, newScale)
{
    boundingVolume = make_unique<AABB>(AABB::generateAABB(*this));
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
                if (child->entity)
                {
                    child->entity->Draw();
                }
            }
        }
    }
}

void Model::DrawWithFrustum(Frustum* frustum)
{
    
    if (boundingVolume->isOnFrustum(frustum, tranform))
    {
        tranform->UpdateMatrix();
        for (int i = 0; i < meshes.size(); ++i)
        {
            renderer->DrawModel3D(this->tranform->modelWorld, meshes[i].VAO, meshes[i].indices, meshes[i].textures);
        }
    }

    std::vector<glm::vec3> vertices = boundingVolume->getVertice();
    renderer->DrawLinesAABB(tranform->modelWorld, vertices);

    //AABB aabb = { glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1.0f, 1.0f, 1.0f)};
    for (auto child : tranform->childs)
    {
         if (child->entity != nullptr && dynamic_cast<Model*>(child->entity))
         {
            dynamic_cast<Model*>(child->entity)->DrawWithFrustum(frustum);
         }
    }
}

void Model::setNewTextures(string currentDirectory, string fileName, bool shouldInvertUVs, string type)
{
    for (BasicMesh& mesh : meshes)
    {
        mesh.setNewTextures(currentDirectory, fileName, shouldInvertUVs, type);
    }
    if (!tranform->childs.empty())
    {
        for (auto child : tranform->childs)
        {
            if (child->entity != nullptr && dynamic_cast<Model*>(child->entity))
            {
                dynamic_cast<Model*>(child->entity)->setNewTextures(currentDirectory, fileName, shouldInvertUVs, type);
            }
        }
    }
}

Model::~Model()
{
    // receiver.unhookEvent(tranform->updateAABB);
    std::cout << "Deleting model";
}

void Model::generateAABB()
{
    glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
    glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());
    recursiveAABB(minAABB, maxAABB, tranform->modelLocal);
    setMinMaxBoundingVolume(minAABB, maxAABB, tranform->modelLocal);

    *boundingVolume = AABB(minAABB, maxAABB);
}


void Model::setMinMaxBoundingVolume(glm::vec3& minAABB, glm::vec3& maxAABB, const glm::mat4& transformMatrix)
{
    for (const BasicMesh& mesh : meshes)
    {
        for (const Vertex& vertex : mesh.vertices)
        {
            glm::vec3 worldPosition = glm::vec3(transformMatrix * glm::vec4(vertex.Position, 1.0f));

            minAABB.x = std::min(minAABB.x, worldPosition.x);
            minAABB.y = std::min(minAABB.y, worldPosition.y);
            minAABB.z = std::min(minAABB.z, worldPosition.z);

            maxAABB.x = std::max(maxAABB.x, worldPosition.x);
            maxAABB.y = std::max(maxAABB.y, worldPosition.y);
            maxAABB.z = std::max(maxAABB.z, worldPosition.z);
        }
    }
}

void Model::recursiveAABB(glm::vec3& minAABB, glm::vec3& maxAABB, const glm::mat4& parentTransformMatrix)
{
    glm::vec3 localMin = minAABB;
    glm::vec3 localMax = maxAABB;

    for (auto child : tranform->childs)
    {
        Model* entity = dynamic_cast<Model*>(child->entity);
        if (entity)
        {
            glm::mat4 childTransformMatrix = parentTransformMatrix * child->getLocalModelMatrix();

            // Calculate local min and max for the current entity
            glm::vec3 childMin = localMin;
            glm::vec3 childMax = localMax;
            entity->recursiveAABB(childMin, childMax, childTransformMatrix);
            entity->setMinMaxBoundingVolume(childMin, childMax,childTransformMatrix);
            
            *entity->boundingVolume = AABB(childMin, childMax);
            minAABB = glm::min(minAABB, childMin);
            maxAABB = glm::max(maxAABB, childMax);
        }
    }


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
