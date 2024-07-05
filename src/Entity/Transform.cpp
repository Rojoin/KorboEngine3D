#include "Transform.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_common.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "Entity.h"
#include "Mesh/BasicMesh.h"


void Transform::setPosition(Vec3 newPosition)
{
    glm::vec3 aux = glm::vec3(newPosition.x, newPosition.y, newPosition.z);
    setLocalPosition(aux);
}

void Transform::setPreviousPosition()
{
    tranlateMatrix = glm::mat4(1.0);
    localPosition = previousPos;
    tranlateMatrix = glm::translate(tranlateMatrix, previousPos);
    UpdateMatrix();
}

void Transform::setLocalPosition(glm::vec3 newPosition)
{
    glm::mat4(1.0);
    glm::vec3 newPos = {newPosition.x, newPosition.y, newPosition.z};
    previousPos = glm::vec3(newPosition.x, newPosition.y, newPosition.z);

    localPosition = newPos;
    tranlateMatrix = glm::translate(glm::mat4(1.0), newPos);
    UpdateMatrix();
}

void Transform::movePosition(Vec3 newPosition)
{
    glm::vec3 aux = glm::vec3(newPosition.x, newPosition.y, newPosition.z);
    movePosition(aux);
}

void Transform::movePosition(glm::vec3 newPosition)
{
    glm::vec3 newPos = {newPosition.x, newPosition.y, newPosition.z};
    previousPos = localPosition;
    localPosition = newPos;
    tranlateMatrix = glm::translate(tranlateMatrix, newPos);
    UpdateMatrix();
}

Vec3 Transform::getGlobalPosition()
{
    glm::vec3 tempPos = glm::vec3(modelWorld[3]);
    return (tempPos);
}

Vec3 Transform::getLocalPosition()
{
    glm::vec3 tempPos = glm::vec3(tranlateMatrix[3]);
    return (tempPos);
}

//Todo: Make rotations.
void Transform::setRotationX(float angle)
{
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(angle), glm::vec3(1.0, 0.0, 0.0));
    localRotation.x += angle;
    UpdateMatrix();
}

void Transform::setRotationY(float angle)
{
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
    localRotation.y += angle;
    UpdateMatrix();
}

void Transform::setRotationZ(float angle)
{
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
    localRotation.z += angle;
    UpdateMatrix();
}

Vec3 Transform::getRotation()
{
    glm::mat3 rotationMatrix3x3 = glm::mat3(rotationMatrix);

    // Extract Euler angles from the 3x3 rotation matrix
    float pitch, yaw, roll;

    // Extract pitch (X-axis rotation)
    pitch = asin(rotationMatrix3x3[1][2]);

    // Check for gimbal lock
    if (cos(pitch) != 0)
    {
        // Extract yaw (Y-axis rotation)
        yaw = atan2(-rotationMatrix3x3[0][2], rotationMatrix3x3[2][2]);

        // Extract roll (Z-axis rotation)
        roll = atan2(-rotationMatrix3x3[1][0], rotationMatrix3x3[1][1]);
    }
    else
    {
        // Gimbal lock case
        yaw = 0; // You can set yaw to any value since roll will be zero
        roll = atan2(rotationMatrix3x3[0][1], rotationMatrix3x3[0][0]);
    }

    return {glm::degrees(pitch), glm::degrees(yaw), glm::degrees(roll)};
}

//Todo: Set Scales for childs
void Transform::setLocalScale(glm::vec3 newScale)
{
    scaleMatrix = glm::scale(glm::mat4(1.0f), newScale);
    localScale = newScale;
    UpdateMatrix();
}

void Transform::setParent(Transform* newTransform)
{
    this->parent = newTransform;
    glm::mat4x4 inverse = glm::inverse(parent->modelLocal);
    glm::mat4x4 aux = inverse * modelLocal;

    //
    //localPosition = aux[3];
    //aux = inverse * rotationMatrix;
    //
    // localRotation = glm::eulerAngles(glm::quat_cast(aux));
    // aux = glm::inverse(parent->modelLocal) * scaleMatrix;
    // localScale = {aux[0][0], aux[1][1], aux[2][2]};
    Transform* current = parent;

    while (current)
    {
        modelLocal = getLocalModelMatrix();
        aux = glm::inverse(current->modelLocal) * modelLocal;
        localPosition = aux[3];
        inverse = glm::inverse(current->modelLocal);

        aux = inverse * rotationMatrix;

        localRotation = glm::eulerAngles(glm::quat_cast(aux));
        aux = inverse * scaleMatrix;
        localScale = {aux[0][0], aux[1][1], aux[2][2]};
        current = current->parent;
    }
    if (newTransform)
    {
        newTransform->childs.push_back(this);
    }
    UpdateMatrixReverse();
}

void Transform::setLocalScale(Vec3 newScale)
{
    glm::vec3 aux = {newScale.x, newScale.y, newScale.z};
    setLocalScale(aux);
}


Vec3 Transform::getPreviousPosition()
{
    return {previousPos.x, previousPos.y, previousPos.z};
}

Transform::Transform(Entity* newEntity) : Component(newEntity)
{
    modelWorld = glm::mat4(1.0f);
    tranlateMatrix = glm::mat4(1.0f);
    scaleMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::mat4(1.0f);
    glm::vec3 newPos(0, 0, 0);
    localPosition = {newPos.x, newPos.y, newPos.z};
    previousPos = glm::vec3(localPosition.x, localPosition.y, localPosition.z);
    tranlateMatrix = glm::translate(tranlateMatrix, newPos);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));


    UpdateMatrix();
    setLocalPosition(localPosition);
}

Transform::Transform(Entity* newEntity, Transform* parent) : Component(newEntity)
{
    modelWorld = glm::mat4(1.0f);
    tranlateMatrix = glm::mat4(1.0f);
    scaleMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::mat4(1.0f);
    glm::vec3 newPos(0, 0, 0);
    localPosition = {newPos.x, newPos.y, newPos.z};
    previousPos = glm::vec3(localPosition.x, localPosition.y, localPosition.z);
    tranlateMatrix = glm::translate(tranlateMatrix, newPos);
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));

    this->parent = parent;
    parent->childs.push_back(this);

    UpdateMatrix();
    setLocalPosition(localPosition);
}

void Transform::setLocalRotation(glm::vec3 angle)
{
    const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f), glm::radians(angle.x), glm::vec3(1.0f, 0.0f, 0.0f));
    const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f), glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f), glm::radians(angle.z), glm::vec3(0.0f, 0.0f, 1.0f));
    rotationMatrix = transformY * transformX * transformZ;
    localRotation = angle;
    UpdateMatrix();
}

//Todo: Rotation
Transform::Transform(Entity* newEntity, glm::vec3 pos, glm::vec3 rot, glm::vec3 newScale) : Component(newEntity)
{
    modelWorld = glm::mat4(1.0f);
    tranlateMatrix = glm::mat4(1.0f);
    scaleMatrix = glm::mat4(1.0f);
    rotationMatrix = glm::mat4(1.0f);
    localPosition = pos;
    localRotation = glm::vec3(0);
    localScale = newScale;
    modelWorld = getLocalModelMatrix();
    setRotationX(rot.x);
    setRotationY(rot.y);
    setRotationZ(rot.z);

    previousPos = localPosition;
    UpdateMatrix();
}

Transform::~Transform()
{
    cout << " Deleting Transform";

    for (Transform* element : childs)
    {
        element->parent = nullptr;
        delete element->entity;
        element->entity = nullptr;
    }
    entity = nullptr;
}


void Transform::UpdateMatrix()
{
    modelWorld = getLocalModelMatrix();
    modelLocal = getLocalModelMatrix();
    if (parent)
        modelWorld = parent->modelWorld * modelWorld;

    globalPosition = modelWorld[3];
    globalRotation = glm::eulerAngles(glm::quat_cast(modelWorld));
    globalScale = {modelWorld[0][0], modelWorld[1][1], modelWorld[2][2]};

    for (auto&& child : childs)
    {
        child->UpdateMatrix();
    }
}

void Transform::UpdateMatrixReverse()
{
    modelLocal = getLocalModelMatrix();
    if (parent)
        modelWorld = parent->modelWorld * getLocalModelMatrix();
    else
        modelWorld = getLocalModelMatrix();

    globalPosition = modelWorld[3];
    globalRotation = glm::eulerAngles(glm::quat_cast(modelWorld));
    globalScale = {modelWorld[0][0], modelWorld[1][1], modelWorld[2][2]};

    for (auto&& child : childs)
    {
        glm::mat4x4 inverse = glm::inverse(modelLocal);
        glm::mat4x4 aux = inverse * child->modelLocal;

        child->localPosition = aux[3];
        aux = glm::inverse(modelLocal) * child->rotationMatrix;
        child->localRotation = glm::eulerAngles(glm::quat_cast(aux));

        aux = modelLocal * child->scaleMatrix;
        Transform* current = parent;

        while (current)
        {
            inverse = glm::inverse(current->modelLocal);
            aux = glm::inverse(current->modelLocal) * child->modelLocal;
            child->localPosition = aux[3];
            aux = glm::inverse(current->modelLocal) * child->rotationMatrix;
            child->localRotation = glm::eulerAngles(glm::quat_cast(aux));
            aux = current->modelLocal * child->scaleMatrix;
            child->localScale = {aux[0][0], aux[1][1], aux[2][2]};
            current = current->parent;
        }
        //aux = scaleInverse * child->scaleMatrix;
        child->UpdateMatrixReverse();
    }
}


glm::mat4 Transform::getLocalModelMatrix()
{
    const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f), glm::radians(localRotation.x),
                                             glm::vec3(1.0f, 0.0f, 0.0f));
    const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f), glm::radians(localRotation.y),
                                             glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f), glm::radians(localRotation.z),
                                             glm::vec3(0.0f, 0.0f, 1.0f));

    // Y * X * Z
    rotationMatrix = transformY * transformX * transformZ;
    tranlateMatrix = glm::translate(glm::mat4(1.0f), localPosition);
    scaleMatrix = glm::scale(glm::mat4(1.0f), localScale);

    return tranlateMatrix * rotationMatrix * scaleMatrix;

    //return tranlate* rotation* scaleMatrix;
}

glm::mat4 Transform::getLocalModelMatrixConst() const
{
    const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f), glm::radians(localRotation.x),
                                         glm::vec3(1.0f, 0.0f, 0.0f));
    const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f), glm::radians(localRotation.y),
                                             glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f), glm::radians(localRotation.z),
                                             glm::vec3(0.0f, 0.0f, 1.0f));

    
    // Y * X * Z
    return (glm::translate(glm::mat4(1.0f), localPosition)) * (transformY * transformX * transformZ) * glm::scale(glm::mat4(1.0f), localScale);
}

glm::vec3 Transform::getRight()
{
    return modelWorld[0];
}

glm::vec3 Transform::getRightConst() const
{
    return modelWorld[0];
}


glm::vec3 Transform::getUp()
{
    return modelWorld[1];
}

glm::vec3 Transform::getUpConst() const
{
    return modelWorld[1];
}

glm::vec3 Transform::getBackward()
{
    return modelWorld[2];
}

glm::vec3 Transform::getBackwardConst() const
{
    return modelWorld[2];
}

glm::vec3 Transform::getForward()
{
    return -modelWorld[2];
}

glm::vec3 Transform::getForwardConst() const
{
    return -modelWorld[2];
}

glm::vec3 Transform::getGlobalScale()
{
    return {glm::length(getRight()), glm::length(getUp()), glm::length(getBackward())};
}

Vec3 Transform::getGlobalScaleVec3()
{
    return {glm::length(getRight()), glm::length(getUp()), glm::length(getBackward())};
}

void Transform::computeModelMatrix()
{
    modelWorld = getLocalModelMatrix();
}

void Transform::computeModelMatrix(const glm::mat4& parentGlobalModelMatrix)
{
    modelWorld = parentGlobalModelMatrix * getLocalModelMatrix();
}
