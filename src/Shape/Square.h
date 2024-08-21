#pragma once
#include "Shape.h"

class EXPORT Square final : public Shape
{
public:
    Square(Renderer* renderer,Vec3 position,Vec3 newScale, bool shouldBeTurnOffByBSP = false);
    Square(Renderer* renderer, Vec4 color,Vec3 position,Vec3 newScale, bool shouldBeTurnOffByBSP = false);
};
