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
    bool collisionX = a->GetPosition().x + a->GetScale().x >= b->GetPosition().x &&
        b->GetPosition().x + b->GetScale().x >= a->GetPosition().x;
    // collision y-axis?
    bool collisionY = a->GetPosition().y + a->GetScale().y >= b->GetPosition().y &&
        b->GetPosition().y + b->GetScale().y >= a->GetPosition().y;
    // collision only if on both axes
    if (collisionX && collisionY)
    {
        Vec3 aux = {a->GetPreviousPosition().x, a->GetPreviousPosition().y, a->GetPreviousPosition().z};
        a->SetPosition(aux);
        aux = {b->GetPreviousPosition().x, b->GetPreviousPosition().y, b->GetPreviousPosition().z};
        b->SetPosition(aux);
        return true;
    }
    return false;
}
