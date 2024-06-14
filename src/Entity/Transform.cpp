#include "Transform.h"

#include <glm/ext/matrix_transform.hpp>

#include "Entity.h"
#include "Mesh/BasicMesh.h"


void Transform::SetPosition(Vec3 newPosition)
{
    glm::vec3 aux = glm::vec3(newPosition.x, newPosition.y, newPosition.z);
    SetPosition(aux);
}

void Transform::SetPreviousPosition()
{
    tranlate = glm::mat4(1.0);
    position = previousPos;
    tranlate = glm::translate(tranlate, previousPos);
    UpdateMatrix();
}

void Transform::SetPosition(glm::vec3 newPosition)
{
    glm::vec3 difference = position - newPosition;
    tranlate = glm::mat4(1.0);
    glm::vec3 newPos = {newPosition.x, newPosition.y, newPosition.z};
    previousPos = glm::vec3(newPosition.x, newPosition.y, newPosition.z);
    position = newPos;
    tranlate = glm::translate(tranlate, newPos);
    UpdateMatrix();
    for (auto element : childs)
    {
        element->MovePosition(difference);
    }
}

void Transform::MovePosition(Vec3 newPosition)
{
    glm::vec3 aux = glm::vec3(newPosition.x, newPosition.y, newPosition.z);
    MovePosition(aux);
}

void Transform::MovePosition(glm::vec3 newPosition)
{
    glm::vec3 newPos = {newPosition.x, newPosition.y, newPosition.z};
    previousPos = position;
    position = newPos;
    tranlate = glm::translate(tranlate, newPos);
    UpdateMatrix();
    for (auto element : childs)
    {
        element->MovePosition(newPosition);
    }
}

Vec3 Transform::GetPosition()
{
    glm::vec3 tempPos = glm::vec3(model[3]);
    //tempPos.x = tranlate[0][3];
    //tempPos.y = tranlate[1][3];
    //tempPos.z = tranlate[2][3];
    //= {model[0][3], model[1][3], model[2][3]};
    return (tempPos);
}

//Todo: Make rotations.
void Transform::SetRotationX(float angle)
{
    rotation = glm::rotate(rotation, glm::radians(angle), glm::vec3(1.0, 0.0, 0.0));
    UpdateMatrix();
}

void Transform::SetRotationY(float angle)
{
    rotation = glm::rotate(rotation, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
    UpdateMatrix();
}

void Transform::SetRotationZ(float angle)
{
    rotation = glm::rotate(rotation, glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
    UpdateMatrix();
}

Vec3 Transform::GetRotation()
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
void Transform::SetScale(glm::vec3 newScale)
{
    scale = glm::mat4(1.0f);
    scaleVector = glm::vec3(newScale.x, newScale.y, newScale.z);
    scale = glm::scale(scale, glm::vec3(newScale.x, newScale.y, newScale.z));
    UpdateMatrix();
}

void Transform::SetScale(Vec3 newScale)
{
    glm::vec3 aux = {newScale.x, newScale.y, newScale.z};
    SetScale(aux);
}

Vec3 Transform::GetScale()
{
    return {scaleVector.x, scaleVector.y, scaleVector.z};
}

Vec3 Transform::GetPreviousPosition()
{
    return {previousPos.x, previousPos.y, previousPos.z};
}

Transform::Transform(Entity* newEntity) : Component(newEntity)
{
    model = glm::mat4(1.0f);
    scaleVector = glm::vec3(1, 1, 1);
    tranlate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotation = glm::mat4(1.0f);
    glm::vec3 newPos(0, 0, 0);
    position = {newPos.x, newPos.y, newPos.z};
    previousPos = glm::vec3(position.x, position.y, position.z);
    tranlate = glm::translate(tranlate, newPos);
    rotation = glm::rotate(rotation, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));


    UpdateMatrix();
    SetPosition(position);
}

//Todo: Rotation
Transform::Transform(Entity* newEntity, glm::vec3 pos, glm::vec3 rot, glm::vec3 newScale) : Component(newEntity)
{
    model = glm::mat4(1.0f);
    scaleVector = glm::vec3(1, 1, 1);
    tranlate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotation = glm::mat4(1.0f);
    glm::vec3 newPos(0, 0, 0);
    position = pos;
    previousPos = glm::vec3(position.x, position.y, position.z);
    tranlate = glm::translate(tranlate, newPos);
    rotation = glm::rotate(rotation, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));


    UpdateMatrix();
    SetPosition(position);
    SetScale(newScale);
}

Transform::~Transform() 
{
    cout << " Deleting Transform";
  
    for (Transform* element : childs)
    {
        delete element;
    }
}

//Todo: Check matrix if has childs
void Transform::UpdateMatrix()
{
    model = tranlate * rotation * scale;
}
