#include "Shape.h"
#include <iostream>

Shape::Shape(Renderer* renderer): Entity2D(renderer)
{
    std::cout << "Shape Created" << std::endl;
}

Shape::~Shape() 
{
    std::cout << "Shape Destroyed" << std::endl;
}

