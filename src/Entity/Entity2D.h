#pragma once
#include "Entity.h"
#include "Globals/dllHeader.h"




class EXPORT Entity2D : public Entity
{
public:
    Entity2D(Renderer* renderer,Vec3 position,Vec3 newScale);
    ~Entity2D() override;
    void Draw() override;
   


};
