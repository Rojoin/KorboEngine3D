#pragma once
#include "Entity/Entity3D.h"

 class EXPORT Cube : public Entity3D
{
public:
    Cube(Renderer* renderer,Vec3 position, Vec3 newScale);
    Cube(Renderer* renderer, Vec3 position, Vec3 newScale, Vec4 color);
};
