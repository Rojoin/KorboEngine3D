#pragma once
#include "Globals/Vec3.h"
#include "Vertex/vertex.h"

class Entity
{
public:
    Entity();
    ~Entity() = default;
    
    virtual void Draw() const =0;
    virtual void SetPositions(float positions[]) const = 0;
    virtual void SetIndices(float indices[]) const = 0;
    virtual float* GetPositions() const = 0;
    virtual float* GetIndices() const = 0;
protected:
    float* positions;
    float* indices;
};
