#pragma once
#include "Entity/Entity3D.h"

 class EXPORT Cube : public Entity3D
{
public:
    Cube(Renderer* renderer,Vec3 position, Vec3 newScale,bool shouldBeTurnOffByBSP = false);
    Cube(Renderer* renderer, Vec3 position, Vec3 newScale, const char* textureLocation,bool shouldBeTurnOffByBSP = false);
};
