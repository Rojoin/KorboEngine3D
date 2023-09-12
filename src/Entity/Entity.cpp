#include "Entity.h"



Entity::Entity(Renderer* renderer)
{
    this->renderer =renderer;
    color = {1,1,1,1};
    cout << "Init Entity";
}

Entity::~Entity()
{
    
}
