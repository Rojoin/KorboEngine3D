#pragma once
#include "Entity.h"
#include "Shader/Material.h"

class EXPORT Entity3D :public Entity
{
protected:
    Material m_material;
    unsigned m_isUsingTexture;
public:
    Entity3D(Renderer* renderer,Vec3 position,Vec3 rotation,Vec3 newScale);
    Entity3D(Renderer* renderer,Vec3 position,Vec3 newScale);
    void setMaterial(Material material);
    ~Entity3D() override;
    void Draw() override;
    
};

