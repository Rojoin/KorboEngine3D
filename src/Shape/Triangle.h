#pragma once
#include "Shape.h"

class EXPORT Triangle final : public Shape
{
public:
    Triangle(Renderer* renderer,Vec3 position, Vec3 newScale);
    Triangle(Renderer* renderer, Vec4 color,Vec3 position, Vec3 newScale);
};
