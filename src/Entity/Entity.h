#pragma once
#include "Renderer/renderer.h"

class Entity
{
public:
    Entity();
    ~Entity() = default;
    
    virtual void Draw() const =0;
};
