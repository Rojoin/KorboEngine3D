#pragma once
#include "Globals/Vec3.h"
#include "Vertex/vertex.h"

class Entity
{
public:
    Entity();
    virtual ~ Entity();
    //Matrix4x4 TRS;
    Vec3 pos;
    bool isEnable;
    Vertex vertex[];
    virtual void Draw() const =0;

private:
};

class Entity2D : public Entity
{
public:
    void Draw() const override;
};

class Shape2D : public Entity2D
{
    
public:
    void Draw() const override;
};

class Entity3D final : public Entity
{
public:
    void Draw() const override;
};
