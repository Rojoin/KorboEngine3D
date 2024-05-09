﻿#include "Colitions.h"
#include <iostream>
#include <cmath>

Colitions::Colitions()
{
    cout << "Colitions Created" << endl;
}

Colitions::~Colitions()
{
    cout << "Colitions Deleted" << endl;
}

bool Colitions::CheckCollitions(Entity2D a, Entity2D b)
{
    float aRight = a.GetPosition().x + abs(a.GetScale().x) / 2;
    float bLeftSide = b.GetPosition().x - abs(b.GetScale().x) / 2;
    float aLeftSide = a.GetPosition().x - abs(a.GetScale().x) / 2;
    float bRightSide = b.GetPosition().x + abs(b.GetScale().x) / 2;
    // collision x-axis?
    bool collisionX = aRight >= bLeftSide &&
        bRightSide >= aLeftSide;


    float aUpSide = a.GetPosition().y + abs(a.GetScale().y) / 2;
    float bDownSide = b.GetPosition().y - abs(b.GetScale().y) / 2;
    float bUpSide = b.GetPosition().y + abs(b.GetScale().y) / 2;
    float aDownSide = a.GetPosition().y - abs(a.GetScale().y) / 2;
    // collision y-axis?
    bool collisionY = aUpSide >= bDownSide &&
        bUpSide >= aDownSide;


    return collisionX && collisionY;
}

bool Colitions::CheckCollitions(Entity2D* a, Entity2D* b)
{
    float aRight = a->GetPosition().x + abs(a->GetScale().x) / 2;
    float bLeftSide = b->GetPosition().x - abs(b->GetScale().x) / 2;
    float aLeftSide = a->GetPosition().x - abs(a->GetScale().x) / 2;
    float bRightSide = b->GetPosition().x + abs(b->GetScale().x) / 2;
    // collision x-axis?
    bool collisionX = aRight >= bLeftSide &&
        bRightSide >= aLeftSide;


    float aUpSide = a->GetPosition().y + abs(a->GetScale().y) / 2;
    float bDownSide = b->GetPosition().y - abs(b->GetScale().y) / 2;
    float bUpSide = b->GetPosition().y + abs(b->GetScale().y) / 2;
    float aDownSide = a->GetPosition().y - abs(a->GetScale().y) / 2;
    // collision y-axis?
    bool collisionY = aUpSide >= bDownSide &&
        bUpSide >= aDownSide;
    // collision only if on both axes


    if (collisionX && collisionY)
    {
        a->SetPreviousPosition();

        b->SetPreviousPosition();
        return true;
    }
    return false;
}
