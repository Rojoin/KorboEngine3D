﻿#include "Entity3D.h"

Entity3D::Entity3D(Renderer* renderer, Vec3 position, Vec3 newScale): Entity(renderer)
{
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
