#pragma once
#include "Entity/Entity2D.h"
#include "Globals/Vec4.h"


class EXPORT Shape : public Entity2D
{
public:
    Shape(Renderer* renderer,Vec3 position, Vec3 newScale,bool shouldBeTurnOffByBSP = false);
    virtual ~Shape() = 0;

private:
 
};


