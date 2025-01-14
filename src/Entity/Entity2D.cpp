#include "Entity2D.h"

#include <algorithm>


Entity2D::Entity2D(Renderer* renderer, Vec3 position,Vec3 rotation, Vec3 newScale,bool shouldBeTurnOffByBSP): Entity(
    renderer, glm::vec3(position.x, position.y, position.z), glm::vec3(rotation.x, rotation.y, rotation.z), glm::vec3(newScale.x,newScale.y,newScale.z),shouldBeTurnOffByBSP)
{
    atribPosSize = 3;
    atribColorSize = 4;
    atribUVSize = 2;
}
Entity2D::Entity2D(Renderer* renderer, Vec3 position, Vec3 newScale,bool shouldBeTurnOffByBSP): Entity(
    renderer, glm::vec3(position.x, position.y, position.z), glm::vec3(1), glm::vec3(newScale.x,newScale.y,newScale.z),shouldBeTurnOffByBSP)
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
    renderer->DrawEntity(VAO, indexSize, color, this->tranform->modelWorld);
}
