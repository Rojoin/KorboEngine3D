#pragma once
#include "Entity.h"

class Component
{
public :
    explicit Component(Entity* entity);

protected:
    Entity* entity = nullptr;
};
