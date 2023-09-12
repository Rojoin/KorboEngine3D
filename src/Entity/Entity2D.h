#pragma once
#include "Entity.h"
#include "Globals/dllHeader.h"

 class EXPORT Entity2D : public Entity
{
public:
    Entity2D(Renderer* renderer);
    ~Entity2D() override;
    void Draw() const override;
protected:
     //Vertex Array Object
     unsigned int VAO;

     //Vertex buffer Object
     unsigned int VBO;
     int vertexSize;
     int atribVertexSize = 3;
     float* vertexPositions;

     //Elements buffer Object
     unsigned int EBO;
     int indexSize;
     int* indices;
};
