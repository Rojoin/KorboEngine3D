#pragma once
#include "Shape/Square.h"
#include "Shape/Triangle.h"

class Colitions
{
public:
    Colitions();
    ~Colitions();
    bool SquareSquareColition(Square a,Square b);
    bool TriangleTriangleColition(Triangle a,Triangle b);
    bool SquareTriangleColition(Square a,Triangle b);
};
