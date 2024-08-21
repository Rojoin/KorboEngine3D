#pragma once
#include "Entity/Entity3D.h"

class EXPORT Pyramid : public Entity3D
{
public:
    Pyramid(Renderer* renderer, Vec3 position, Vec3 newScale, bool shouldBeTurnOffByBSP = false);
    Pyramid(Renderer* renderer, Vec3 position, Vec3 newScale, Vec4 color, bool shouldBeTurnOffByBSP = false);
};
