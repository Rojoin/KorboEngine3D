#pragma once
#include "Shape.h"

class EXPORT Square final : public Shape
{
public:
    Square(Renderer* renderer,Vec3 position,Vec3 newScale);
    Square(Renderer* renderer, Vec4 color,Vec3 position,Vec3 newScale);
};
