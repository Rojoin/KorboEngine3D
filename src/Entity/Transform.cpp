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
    tranlate = glm::mat4(1.0);
    position = previousPos;
    tranlate = glm::translate(tranlate, previousPos);
    UpdateMatrix();
}

void Transform::setLocalPosition(glm::vec3 newPosition)
{
    glm::vec3 difference = position - newPosition;
    tranlate = glm::mat4(1.0);
    glm::vec3 newPos = {newPosition.x, newPosition.y, newPosition.z};
    previousPos = glm::vec3(newPosition.x, newPosition.y, newPosition.z);
    position = newPos;
    tranlate = glm::translate(tranlate, newPos);
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
    previousPos = position;
    position = newPos;
    tranlate = glm::translate(tranlate, newPos);
    UpdateMatrix();
}

Vec3 Transform::getGlobalPosition()
{
    glm::vec3 tempPos = glm::vec3(model[3]);
    return (tempPos);
}

Vec3 Transform::getLocalPosition()
{
    glm::vec3 tempPos = glm::vec3(tranlate[3]);
    return (tempPos);
}

//Todo: Make rotations.
void Transform::setRotationX(float angle)
{
    rotation = glm::rotate(rotation, glm::radians(angle), glm::vec3(1.0, 0.0, 0.0));
    eulerRot.x += angle;
    UpdateMatrix();
}

void Transform::setRotationY(float angle)
{
    rotation = glm::rotate(rotation, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
    eulerRot.y += angle;
    UpdateMatrix();
}

void Transform::setRotationZ(float angle)
{
    rotation = glm::rotate(rotation, glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
    eulerRot.z += angle;
    UpdateMatrix();
}

Vec3 Transform::getRotation()
{
    glm::mat3 rotationMatrix3x3 = glm::mat3(rotation);

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
    scaleMatrix = glm::mat4(1.0f);
    scaleVector = glm::vec3(newScale.x, newScale.y, newScale.z);
    scaleMatrix = glm::scale(scaleMatrix, glm::vec3(newScale.x, newScale.y, newScale.z));
    scale = newScale;
    UpdateMatrix();
}

void Transform::setParent(Transform* newTransform)
{
    this->parent = newTransform;
    UpdateMatrix();
    if (newTransform)
    {
        newTransform->childs.push_back(this);
    }
}

void Transform::setLocalScale(Vec3 newScale)
{
    glm::vec3 aux = {newScale.x, newScale.y, newScale.z};
    setLocalScale(aux);
}

Vec3 Transform::getScale()
{
    return {scaleVector.x, scaleVector.y, scaleVector.z};
}

Vec3 Transform::getPreviousPosition()
{
    return {previousPos.x, previousPos.y, previousPos.z};
}

Transform::Transform(Entity* newEntity) : Component(newEntity)
{
    model = glm::mat4(1.0f);
    scaleVector = glm::vec3(1, 1, 1);
    tranlate = glm::mat4(1.0f);
    scaleMatrix = glm::mat4(1.0f);
    rotation = glm::mat4(1.0f);
    glm::vec3 newPos(0, 0, 0);
    position = {newPos.x, newPos.y, newPos.z};
    previousPos = glm::vec3(position.x, position.y, position.z);
    tranlate = glm::translate(tranlate, newPos);
    rotation = glm::rotate(rotation, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));


    UpdateMatrix();
    setLocalPosition(position);
}

void Transform::setLocalRotation(glm::vec3 angle)
{
    const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f), glm::radians(angle.x), glm::vec3(1.0f, 0.0f, 0.0f));
    const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f), glm::radians(angle.y), glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f), glm::radians(angle.z), glm::vec3(0.0f, 0.0f, 1.0f));
    rotation = transformY * transformX * transformZ;
    eulerRot = angle;
    UpdateMatrix();
}

//Todo: Rotation
Transform::Transform(Entity* newEntity, glm::vec3 pos, glm::vec3 rot, glm::vec3 newScale) : Component(newEntity)
{
    model = glm::mat4(1.0f);
    scaleVector = glm::vec3(1, 1, 1);
    tranlate = glm::mat4(1.0f);
    scaleMatrix = glm::mat4(1.0f);
    rotation = glm::mat4(1.0f);
    glm::vec3 newPos(0, 0, 0);
    position = pos;
    previousPos = glm::vec3(position.x, position.y, position.z);
    tranlate = glm::translate(tranlate, newPos);
    rotation = glm::rotate(rotation, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
    scale = newScale;
    eulerRot = rot;
    UpdateMatrix();
    setLocalPosition(position);
    setLocalScale(newScale);
    setLocalRotation(rot);
}

Transform::~Transform()
{
    cout << " Deleting Transform";

    for (Transform* element : childs)
    {
        element->parent = nullptr;
        delete element->entity;
    }
}


void Transform::UpdateMatrix()
{
    if (parent)
        model = parent->model * getLocalModelMatrix();
    else
        model = getLocalModelMatrix();

    for (auto&& child : childs)
    {
        child->UpdateMatrix();
    }
}

void Transform::UpdateMatrixReverse()
{
    //Todo: multiplicar la matrix local para que quede igual a la parent
    glm::mat4x4 previousWorldMatrix = model;
    if (parent)
        model = parent->model * getLocalModelMatrix();
    else
        model = getLocalModelMatrix();

    for (auto&& child : childs)
    {
        glm::mat4 newLocalMatrix = glm::inverse(parent ? parent->model : glm::mat4(1.0f)) * previousWorldMatrix;

        // Decompose newLocalMatrix into position, rotation, and scale components
        glm::vec3 skew;
        glm::vec4 perspective;
        glm::quat orientation;
        glm::vec3 scale, translation;
        glm::decompose(newLocalMatrix, scale, orientation, translation, skew, perspective);

        // Set the child's local transformation
        child->setLocalPosition(translation);
        child->setLocalRotation(glm::eulerAngles(orientation));
        child->setLocalScale(scale);
      //  child->UpdateMatrixReverse();
    }
}


glm::mat4 Transform::getLocalModelMatrix()
{
     const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f), glm::radians(eulerRot.x), glm::vec3(1.0f, 0.0f, 0.0f));
     const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f), glm::radians(eulerRot.y), glm::vec3(0.0f, 1.0f, 0.0f));
     const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f), glm::radians(eulerRot.z), glm::vec3(0.0f, 0.0f, 1.0f));
    
     // Y * X * Z
     const glm::mat4 rotationMatrix = transformY * transformX * transformZ;
    
     // translation * rotation * scale (also know as TRS matrix)
     return glm::translate(glm::mat4(1.0f), position) * rotationMatrix * glm::scale(glm::mat4(1.0f), scale);

    //return tranlate* rotation* scaleMatrix;
}

glm::vec3 Transform::getRight()
{
    return model[0];
}


glm::vec3 Transform::getUp()
{
    return model[1];
}

glm::vec3 Transform::getBackward()
{
    return model[2];
}

glm::vec3 Transform::getForward()
{
    return -model[2];
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
    model = getLocalModelMatrix();
}

void Transform::computeModelMatrix(const glm::mat4& parentGlobalModelMatrix)
{
    model = parentGlobalModelMatrix * getLocalModelMatrix();
}
