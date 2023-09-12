#pragma once
#include "Globals/Vec4.h"
#include "Renderer/renderer.h"
#include "Globals/dllHeader.h"

class EXPORT Entity
{
public:
    Entity(Renderer* renderer);
    virtual ~Entity();
    virtual void Draw() =0;

protected:
    Renderer* renderer;
    Vec4 color;
};
