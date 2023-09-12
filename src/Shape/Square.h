#pragma once
#include "Shape.h"

class EXPORT Square final : public Shape
{
public:
    Square(Renderer* renderer);
    Square(Renderer* renderer, Vec4 color);
};
