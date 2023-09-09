#pragma once
#include "Globals/Vec4.h"
#include "Renderer/renderer.h"

class Entity
{
public:
    Entity(Renderer* renderer);
    virtual ~Entity();
    virtual void Draw() const =0;

protected:
    Renderer* renderer;
    Vec4 color;
};
