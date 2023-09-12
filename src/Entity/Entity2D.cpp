#include "Entity2D.h"

Entity2D::Entity2D(Renderer* renderer) : Entity(renderer)
{
    
}

Entity2D::~Entity2D()
{
    renderer->DeleteObjects(VAO, VBO, EBO);
}

void Entity2D::Draw() 
{
    renderer->DrawEntity2D(VAO, indexSize,color);
}
