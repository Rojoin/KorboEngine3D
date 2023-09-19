#pragma once
#include "Entity.h"
#include "Globals/dllHeader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

 class EXPORT Entity2D : public Entity
{
public:
    Entity2D(Renderer* renderer);
    ~Entity2D() override;
    void Draw() override;
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
     //Transform Matrix
     glm::mat4x4 TRS;
};
