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
    void SetPreviousPosition();
    void MovePosition(Vec3 newPosition);
    Vec3 GetPosition();
    void SetRotationX(float angle);
    void SetRotationY(float angle);
    void SetRotationZ(float angle);
    void SetScale(Vec3 newScale);
    Vec3 GetScale();
    Vec3 GetPreviousPosition();

protected:
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
    //Transform Matrix
    glm::mat4x4 model;
    glm::mat4 tranlate;
    glm::mat4 rotation;
    glm::mat4 scale;
    //Transform Vectors
    glm::vec3 position;
    Vec3 scaleVector;
    glm::vec3 previousPos;

    void SetPosition(glm::vec3 newPosition);
    void UpdateMatrix();
};
