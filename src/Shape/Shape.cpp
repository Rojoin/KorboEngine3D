#include "Shape.h"
#include <iostream>

Shape::Shape(Renderer* renderer,Vec3 position, Vec3 newScale, bool shouldBeTurnOffByBSP): Entity2D(renderer,position,{0,0,0},newScale,  shouldBeTurnOffByBSP)
{
    std::cout << "Shape Created" << std::endl;
}

Shape::~Shape() 
{
    std::cout << "Shape Destroyed" << std::endl;
}

