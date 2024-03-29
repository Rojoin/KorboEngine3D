#pragma once
#include "Entity.h"

class EXPORT Entity3D :public Entity
{

public:
    Entity3D(Renderer* renderer,Vec3 position,Vec3 newScale);
    ~Entity3D() override;
    void Draw() override;
    
};

