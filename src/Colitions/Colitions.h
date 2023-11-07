#pragma once
#include "Entity/Entity2D.h"

class EXPORT Colitions
{
public:
    Colitions();
    ~Colitions();
    static bool CheckCollitions(Entity2D a,Entity2D b);
    static bool CheckCollitions(Entity2D *a,Entity2D *b);
};
