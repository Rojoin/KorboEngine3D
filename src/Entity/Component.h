#pragma once
#include "Globals/dllHeader.h"

class Entity;

class EXPORT Component
{
public :
    explicit Component(Entity* entity);
    virtual ~Component() = 0;
    Entity* entity;

protected:
};
