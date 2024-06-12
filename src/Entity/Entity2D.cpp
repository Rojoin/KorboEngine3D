#include "Entity2D.h"

#include <algorithm>


Entity2D::Entity2D(Renderer* renderer, Vec3 position, Vec3 newScale): Entity(renderer)
{
    atribPosSize = 3;
    atribColorSize = 4;
    atribUVSize = 2;
}


Entity2D::~Entity2D()
{
}

//Todo: Change methods to be in graphics renderer
void Entity2D::Draw()
{
    renderer->DrawEntity(VAO, indexSize, color, this->tranform->model);
}
