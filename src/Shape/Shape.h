#pragma once
#include "Globals/Vec4.h"

enum ShapeType {TRIANGLE,SQUARE};

class Shape
{
public:
    Shape();
    ~Shape();
    void SetType(ShapeType type);
    ShapeType GetType;
    void SetPositions(float positions[]);
   // float*[] GetPositions;

protected:
    ShapeType type;
    float* positions[];
    float* index[];
    Vec4 color;
};
