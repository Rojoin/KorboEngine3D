﻿#include "Entity3D.h"

Entity3D::Entity3D(Renderer* renderer, Vec3 position, Vec3 newScale): Entity(renderer)
{
   this->tranform->model = glm::mat4(1.0f);
     this->tranform->scaleVector = glm::vec3(newScale.x,newScale.y,newScale.z);
     this->tranform->tranlate = glm::mat4(1.0f);
     this->tranform->scale = glm::mat4(1.0f);
     this->tranform->rotation = glm::mat4(1.0f);
    glm::vec3 newPos(position.x, position.y, position.z);
    position = {newPos.x,newPos.y, newPos.z};
    previousPos =  glm::vec3(position.x, position.y, position.z);
    tranlate = glm::translate(tranlate, newPos);
    rotation = glm::rotate(rotation, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
    this->tranform->previousPos =  glm::vec3(position.x, position.y, position.z);
    this->tranform->rotation = glm::rotate(this->tranform->rotation, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));

    atribPosSize = 3;
    atribColorSize = 4;
    atribUVSize = 2;
    
    UpdateMatrix();
    SetScale(newScale);
    SetPosition(position);
    vertexPositions = nullptr;
    indices = nullptr;
}

void Entity3D::setMaterial(Material material)
{
    m_material = material;
    
}

Entity3D::~Entity3D()
{
    renderer->DeleteObjects(VAO, VBO, EBO);
    delete vertexPositions;
    delete indices;
}

void Entity3D:: Draw() 
{
    //renderer->DrawEntity(VAO, indexSize, color, model);
    renderer->DrawEntity3D(VAO, indexSize, color, model, m_material, textureId, m_isUsingTexture);
}
