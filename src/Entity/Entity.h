#pragma once
#include "Transform.h"
#include "Renderer/renderer.h"
#include "Globals/dllHeader.h"


class EXPORT Entity
{
public:
    Entity(Renderer* renderer, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    Entity(Renderer* renderer, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale,Transform* parent);
    Entity(glm::vec3 position);
    Entity();
    virtual ~Entity() =0;
    virtual void Draw() =0;
    Transform* tranform;

    
    void SetPosition(Vec3 newPosition);
    void SetPosition(glm::vec3 newPosition);
    void SetPreviousPosition();
    void MovePosition(Vec3 newPosition);
    void MovePosition(glm::vec3 newPosition);
    Vec3 GetPosition();
    void SetRotationX(float angle);
    void SetRotationY(float angle);
    void SetRotationZ(float angle);
    Vec3 GetRotation();
    void SetScale(Vec3 newScale);
    Vec3 GetScale();
    Vec3 GetPreviousPosition();
    void SetParent(Entity* newParent = nullptr);
    Renderer* GetRenderer();


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
private:
};
