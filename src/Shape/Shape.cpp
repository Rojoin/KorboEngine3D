#include "Shape.h"
#include <iostream>

Shape::Shape(Renderer* renderer,Vec3 position, Vec3 newScale): Entity2D(renderer,position,{0,0,0},newScale)
{
    std::cout << "Shape Created" << std::endl;
}

Shape::~Shape() 
{
    std::cout << "Shape Destroyed" << std::endl;
}

