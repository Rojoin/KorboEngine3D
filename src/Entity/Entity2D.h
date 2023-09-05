#pragma once
#include "Entity.h"

class Entity2D : Entity
{
public:
    Entity2D();
    ~Entity2D() = default;
    void Draw() const override;
protected:
    
};
