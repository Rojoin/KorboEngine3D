#pragma once
#include "Transform.h"
#include "Renderer/renderer.h"
#include "Globals/dllHeader.h"


class EXPORT Entity
{
public:
    Entity(Renderer* renderer);
    Entity(glm::vec3 position);
    Entity();
    virtual ~Entity() = 0;
    virtual void Draw() =0;
    Transform* tranform;
protected:
    Renderer* renderer;
    Vec4 color;
    //Vertex Array Object
    unsigned int VAO;

    //Vertex buffer Object
    unsigned int VBO;
    int vertexSize;
    int atribPosSize = 3;
    int atribColorSize = 4;
    float* vertexPositions;

    unsigned int textureId;
    int uvSize;
    int atribUVSize = 2;
    
    //Elements buffer Object
    unsigned int EBO;
    int indexSize;
    int* indices;
};
