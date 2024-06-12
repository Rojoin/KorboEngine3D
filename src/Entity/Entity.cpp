#include "Entity.h"


//Todo: Add Entity with vector3
Entity::Entity(Renderer* renderer)
{
    cout << "Init Entity";
    tranform = new Transform(this);
}

Entity::Entity()
{
    tranform = new Transform(this);
}

Entity::Entity(glm::vec3 position)
{
    tranform = new Transform(this, position);
}

Entity::~Entity()
{
    delete this->tranform;
  //  delete graphicsRenderer;
}
