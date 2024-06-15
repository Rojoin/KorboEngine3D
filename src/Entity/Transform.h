#pragma once
#include <list>
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
    Transform(Entity* newEntity, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
    ~Transform() override;


    void setPosition(Vec3 newPosition);
    void setLocalPosition(glm::vec3 newPosition);
    void setPreviousPosition();
    void movePosition(Vec3 newPosition);
    void movePosition(glm::vec3 newPosition);
    Vec3 getGlobalPosition();
    Vec3 getLocalPosition();
    void setLocalRotation(glm::vec3 angle);
    void setRotationX(float angle);
    void setRotationY(float angle);
    void setRotationZ(float angle);
    Vec3 getRotation();
    void setLocalScale(Vec3 newScale);
    void setLocalScale(glm::vec3 newScale);
    void setParent(Transform* newTransform = nullptr);
    Vec3 getScale();
    Vec3 getPreviousPosition();
    glm::vec3 getGlobalScale();
    Vec3 getGlobalScaleVec3();
    glm::vec3 getForward();
    glm::vec3 getBackward();
    glm::vec3 getUp();
    glm::vec3 getRight();


    Transform* parent;
    std::vector<Transform*> childs;
    glm::mat4x4 model;
    glm::mat4x4 globalModel;
    glm::mat4 tranlate;

    glm::mat4 scaleMatrix;
    //Transform Vectors
    glm::mat4 rotation;
    Vec3 scaleVector;
    glm::vec3 previousPos;
    glm::vec3 position;
    glm::vec3 eulerRot;
    glm::vec3 scale;
    void UpdateMatrix();
    void UpdateMatrixReverse();

protected:
    //Transform Matrix
    glm::mat4 getLocalModelMatrix();
    void computeModelMatrix();
    void computeModelMatrix(const glm::mat4& parentGlobalModelMatrix);
};
