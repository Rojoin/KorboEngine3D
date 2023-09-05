#include "Shape.h"
#include <iostream>

Shape::Shape(): Entity2D()
{
    std::cout << "Shape " << type << "Created" << std::endl;
}

Shape::~Shape()
{
    std::cout << "Shape " << type << "Destroyed" << std::endl;
}

void Shape::SetType(ShapeType type)
{
    this->type = type;
}
ShapeType Shape::GetType()
{
    return  type;
}
    
void Shape::SetPositions(float positions[])
{
    this->positions = positions;
}
float* Shape::GetPositions()
{
    return  positions;
}

void Shape::Setindices(float indices[])
{
    this->indices = indices;
}
float* Shape::Getindices()
{
    return indices;
}
    
void Shape::SetColor(Vec4 color)
{
    this->color = color;
}
Vec4 Shape::GetColor()
{
    return color;
}