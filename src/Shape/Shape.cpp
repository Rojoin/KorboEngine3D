#include "Shape.h"
#include <iostream>

Shape::Shape(ShapeType type): Entity2D()
{
    this->type = type;
    color = Vec4();
    std::cout << "Shape " << this->type << "Created" << std::endl;
}

Shape::~Shape() 
{
    std::cout << "Shape " << this->type << "Destroyed" << std::endl;
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
    return positions;
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

void Shape::SetShapeVertexBuffer(unsigned int vertexBuffer)
{
    this->vertexBuffer = vertexBuffer;
}
unsigned int Shape::GetShapeVertexBuffer()
{
    return vertexBuffer;
}