#pragma once
#include "Entity.h"
#include "Globals/dllHeader.h"




class EXPORT Entity2D : public Entity
{
public:
    Entity2D(Renderer* renderer, Vec3 position,Vec3 rotation, Vec3 newScale,bool shouldBeTurnOffByBSP = false);
    Entity2D(Renderer* renderer, Vec3 position, Vec3 newScale, bool shouldBeTurnOffByBSP = false);
    ~Entity2D() override;
    void Draw() override;
   


};
