#include "Entity2D.h"


Entity2D::Entity2D(Renderer* renderer, Vec3 position, Vec3 newScale): Entity(renderer)
{
    model = glm::mat4(1.0f);
    scaleVector = glm::vec3(newScale.x,newScale.y,newScale.z);
    tranlate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotation = glm::mat4(1.0f);
    glm::vec3 newPos(position.x, position.y, position.z);
    position = {newPos.x,newPos.y, newPos.z};
    previousPos =  glm::vec3(position.x, position.y, position.z);
    tranlate = glm::translate(tranlate, newPos);
    rotation = glm::rotate(rotation, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
  
    UpdateMatrix();
    SetScale(newScale);
    SetPosition(newPos);
}


Entity2D::~Entity2D()
{
    renderer->DeleteObjects(VAO, VBO, EBO);
    delete vertexPositions;
    delete indices;
}

void Entity2D::Draw()
{
    renderer->DrawEntity2D(VAO, indexSize, color, model);
}

void Entity2D::SetPosition(Vec3 newPosition)
{
    tranlate = glm::mat4(1.0);
    glm::vec3 newPos = {newPosition.x, newPosition.y, newPosition.z};
    previousPos = position;
    position = newPos;
    tranlate = glm::translate(tranlate, newPos);
    UpdateMatrix();
}
void Entity2D::SetPreviousPosition()
{
    tranlate = glm::mat4(1.0);
    position = previousPos;
    tranlate = glm::translate(tranlate, previousPos);
    UpdateMatrix();
}
void Entity2D::SetPosition(glm::vec3 newPosition)
{
    tranlate = glm::mat4(1.0);
    glm::vec3 newPos = {newPosition.x, newPosition.y, newPosition.z};
    previousPos =  glm::vec3(newPosition.x, newPosition.y, newPosition.z);
    position = newPos;
    tranlate = glm::translate(tranlate, newPos);
    UpdateMatrix();
}

void Entity2D::MovePosition(Vec3 newPosition)
{
    glm::vec3 newPos = {newPosition.x, newPosition.y, newPosition.z};
    previousPos = position;
    position = newPos;
    tranlate = glm::translate(tranlate, newPos);
    UpdateMatrix();
}

Vec3 Entity2D::GetPosition()
{
    glm::vec3 tempPos = glm::vec3(model[3]);
    //tempPos.x = tranlate[0][3];
    //tempPos.y = tranlate[1][3];
    //tempPos.z = tranlate[2][3];
    //= {model[0][3], model[1][3], model[2][3]};
    return (tempPos);
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
    scale = glm::mat4(1.0f);
    scaleVector = glm::vec3(newScale.x,newScale.y,newScale.z);
    scale = glm::scale(scale, glm::vec3(newScale.x, newScale.y, newScale.z));
    UpdateMatrix();
}

Vec3 Entity2D::GetScale()
{
    return { scaleVector.x,scaleVector.y,scaleVector.z };
}

Vec3 Entity2D::GetPreviousPosition()
{
    return {previousPos.x, previousPos.y, previousPos.z};
}

void Entity2D::UpdateMatrix()
{
    model = tranlate * rotation * scale;
}
