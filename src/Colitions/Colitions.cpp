#include "Colitions.h"
#include <iostream>

Colitions::Colitions()
{
    cout << "Colitions Created" << endl;
}

Colitions::~Colitions()
{
    cout << "Colitions Deleted" << endl;
}

bool Colitions::SquareSquareColition(Square a, Square b)
{
    return false;
}

bool Colitions::TriangleTriangleColition(Triangle a, Triangle b)
{
    return false; 
}

bool Colitions::SquareTriangleColition(Square a, Triangle b)
{
    return false;
}





