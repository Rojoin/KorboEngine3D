#pragma once
#include "Entity/Entity2D.h"
#include "Globals/Vec4.h"


class Shape : public Entity2D
{
public:
    Shape(Renderer* renderer);
    virtual ~Shape() = 0;

private:
 
};


