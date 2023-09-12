#pragma once
#include "Shape.h"

class Square final : public Shape
{
public:
    Square(Renderer* renderer);
    Square(Renderer* renderer, Vec4 color);
};
