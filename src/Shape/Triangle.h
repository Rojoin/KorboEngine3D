#pragma once
#include "Shape.h"

class EXPORT Triangle final : public Shape
{
public:
    Triangle(Renderer* renderer);
    Triangle(Renderer* renderer, Vec4 color);
};
