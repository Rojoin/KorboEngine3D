#pragma once
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "Component.h"
#include "Globals/Vec3.h"
#include "Globals/dllHeader.h"

class EXPORT Transform : public Component
{
public:
    explicit Transform(Entity* newEntity);
    Transform(Entity* newEntity, glm::vec3 pos);
    ~Transform();

    
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



    
    Transform* parent;
    std::vector<Transform*> childs;
    glm::mat4x4 model;
    glm::mat4 tranlate;

    glm::mat4 scale;
    //Transform Vectors
    glm::mat4 rotation;
    Vec3 scaleVector;
    glm::vec3 previousPos;
    glm::vec3 position;
    void UpdateMatrix();
protected:
    //Transform Matrix
};
