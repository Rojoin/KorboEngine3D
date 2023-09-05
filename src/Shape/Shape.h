#pragma once
#include "Entity/Entity2D.h"
#include "Globals/Vec4.h"

enum ShapeType {TRIANGLE,SQUARE};

class  Shape : Entity2D
{
public:
    Shape(ShapeType type);
    ~Shape();
    
    void SetType(ShapeType type);
    ShapeType GetType();
    
    void SetPositions(float positions[]);
    float* GetPositions();

    void Setindices(float indices[]);
    float* Getindices();
    
    void SetColor(Vec4 color);
    Vec4 GetColor();

    void SetShapeVertexBuffer(unsigned int vertexBuffer);
    unsigned int GetShapeVertexBuffer();
private:
    float* positions;
    float* indices;
    unsigned int vertexBuffer;
    ShapeType type;
    Vec4 color;
};
