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

bool Colitions::CheckCollitions(Entity2D a, Entity2D b)
{
    // collision x-axis?
    bool collisionX = a.GetPosition().x + a.GetScale().x >= b.GetPosition().x &&
        b.GetPosition().x + b.GetScale().x >= a.GetPosition().x;
    // collision y-axis?
    bool collisionY = a.GetPosition().y + a.GetScale().y >= b.GetPosition().y &&
        b.GetPosition().y + b.GetScale().y >= a.GetPosition().y;
    // collision only if on both axes

    
    return collisionX && collisionY;
}

bool Colitions::CheckCollitions(Entity2D* a, Entity2D* b)
{
    // collision x-axis?
    bool collisionX = a->GetPosition().x + a->GetScale().x/2 >= b->GetPosition().x - b->GetScale().x/2 &&
        b->GetPosition().x + b->GetScale().x/2 >= a->GetPosition().x- a->GetScale().x/2;
    // collision y-axis?
    bool collisionY = a->GetPosition().y + a->GetScale().y/2 >= b->GetPosition().y - b->GetScale().y/2 &&
        b->GetPosition().y + b->GetScale().y/2 >= a->GetPosition().y - a->GetScale().y/2;
    // collision only if on both axes

     collisionX =  a->GetPosition().x - ( a->GetScale().x / 2) +  a->GetScale().x >= b->GetPosition().x - (b->GetScale().x / 2)
        && b->GetPosition().x - (b->GetScale().x / 2) + b->GetScale().x >=  a->GetPosition().x - ( a->GetScale().x / 2);

     collisionY =  a->GetPosition().y - ( a->GetScale().y / 2) +  a->GetScale().y >= b->GetPosition().y - (b->GetScale().y / 2)
        && b->GetPosition().y - (b->GetScale().y / 2) + b->GetScale().y >=  a->GetPosition().y - ( a->GetScale().y / 2);

    if (collisionX && collisionY)
    {
        
        a->SetPreviousPosition();
   
        b->SetPreviousPosition();
        return true;
    }
    return false;
}
