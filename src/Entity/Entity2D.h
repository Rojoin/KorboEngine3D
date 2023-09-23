#pragma once
#include "Entity.h"
#include "Globals/dllHeader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Globals/Vec3.h"

class EXPORT Entity2D : public Entity
{
public:
    Entity2D(Renderer* renderer,Vec3 position,Vec3 newScale);
    ~Entity2D() override;
    void Draw() override;
    void SetPosition(Vec3 newPosition);
    Vec3 GetPosition();
    void SetRotationX(float angle);
    void SetRotationY(float angle);
    void SetRotationZ(float angle);
    void SetScale(Vec3 newScale);
    Vec3 GetScale();

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
    glm::mat4x4 model;
    glm::mat4 tranlate;
    glm::mat4 rotation;
    glm::mat4 scale;

    void UpdateMatrix();
};
