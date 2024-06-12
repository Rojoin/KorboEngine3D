#include "Entity3D.h"

Entity3D::Entity3D(Renderer* renderer, Vec3 position, Vec3 newScale): Entity(renderer)
{
    this->tranform->model = glm::mat4(1.0f);
    this->tranform->scaleVector = glm::vec3(newScale.x, newScale.y, newScale.z);
    this->tranform->tranlate = glm::mat4(1.0f);
    this->tranform->scale = glm::mat4(1.0f);
    this->tranform->rotation = glm::mat4(1.0f);
    glm::vec3 newPos(position.x, position.y, position.z);
    position = {newPos.x, newPos.y, newPos.z};
    this->tranform->previousPos = glm::vec3(position.x, position.y, position.z);
    this->tranform->tranlate = glm::translate(this->tranform->tranlate, newPos);
    this->tranform->rotation = glm::rotate(this->tranform->rotation, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));


    this->tranform->UpdateMatrix();
    this->tranform->SetScale(newScale);
    this->tranform->SetPosition(position);
    atribPosSize = 3;
    atribColorSize = 4;
    atribUVSize = 2;
    vertexPositions = nullptr;
    indices = nullptr;
}

void Entity3D::setMaterial(Material material)
{
    m_material = material;
}

Entity3D::~Entity3D()
{
}

//Todo: Renderer class must have all draws for all types of objects
void Entity3D::Draw()
{
    renderer->DrawEntity(VAO, indexSize, color, this->tranform->model);
    // graphicsRenderer-> renderer->DrawEntity3D(graphicsRenderer->VAO, graphicsRenderer->indexSize, graphicsRenderer->color, this->tranform->model, m_material, graphicsRenderer->textureId, m_isUsingTexture);
}
