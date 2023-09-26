#include "Entity2D.h"


Entity2D::Entity2D(Renderer* renderer,Vec3 position,Vec3 newScale): Entity(renderer)
{
    model = glm::mat4(1.0f);

    tranlate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotation = glm::mat4(1.0f);
    glm::vec3 newPos(position.x, position.y, position.z);
    tranlate = glm::translate(tranlate, newPos);
    rotation = glm::rotate(rotation, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
    scale = glm::scale(scale, glm::vec3(1, 1, scale[2][2]));
    UpdateMatrix();
    SetScale(newScale);
}


Entity2D::~Entity2D()
{
    renderer->DeleteObjects(VAO, VBO, EBO);
}

void Entity2D::Draw()
{
    renderer->DrawEntity2D(VAO, indexSize, color, model);
}

void Entity2D::SetPosition(Vec3 newPosition)
{
    glm::vec3 newPos = {newPosition.x, newPosition.y, newPosition.z};
    tranlate = glm::translate(tranlate, newPos);
    UpdateMatrix();
}

Vec3 Entity2D::GetPosition()
{
    return {tranlate[0][3], tranlate[1][3], tranlate[2][3]};
}

void Entity2D::SetRotationX(float angle)
{
    rotation = glm::rotate(rotation, glm::radians(angle), glm::vec3(1.0, 0.0, 0.0));
    UpdateMatrix();
}

void Entity2D::SetRotationY(float angle)
{
    rotation = glm::rotate(rotation, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
    UpdateMatrix();
}

void Entity2D::SetRotationZ(float angle)
{
    rotation = glm::rotate(rotation, glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
    UpdateMatrix();
}

void Entity2D::SetScale(Vec3 newScale)
{
    scale = glm::scale(scale, glm::vec3(newScale.x, newScale.y, scale[2][2]));
    UpdateMatrix();
}

Vec3 Entity2D::GetScale()
{
    return {scale[0][0], scale[1][1], scale[2][2]};
}

void Entity2D::UpdateMatrix()
{
    model = tranlate * rotation * scale;
}
