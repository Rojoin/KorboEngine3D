#include "Entity.h"



Entity::Entity(Renderer* renderer, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    cout << "Init Entity";
    tranform = new Transform(this, position, rotation, scale);
    this->renderer = renderer;
}
Entity::Entity(Renderer* renderer, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale,Transform* parent)
{
    cout << "Init Entity";
    tranform = new Transform(this,parent);
    this->renderer = renderer;
}

Entity::Entity()
{
    tranform = new Transform(this);
}

Entity::Entity(glm::vec3 position)
{
    tranform = new Transform(this);
}

Entity::~Entity()
{
    delete this->tranform;
    cout << "Deleting Entity";
}

void Entity::SetPosition(Vec3 newPosition)
{
    tranform->setPosition(newPosition);
}

void Entity::SetPosition(glm::vec3 newPosition)
{
    tranform->setLocalPosition(newPosition);
}

void Entity::SetPreviousPosition()
{
    tranform->setPreviousPosition();
}

void Entity::MovePosition(Vec3 newPosition)
{
    tranform->movePosition(newPosition);
}

void Entity::MovePosition(glm::vec3 newPosition)
{
    tranform->movePosition(newPosition);
}

Vec3 Entity::GetPosition()
{
    return {tranform->getGlobalPosition().x, tranform->getGlobalPosition().y, tranform->getGlobalPosition().z};
}

void Entity::SetRotationX(float angle)
{
    tranform->setRotationX(angle);
}

void Entity::SetRotationY(float angle)
{
    tranform->setRotationY(angle);
}

void Entity::SetRotationZ(float angle)
{
    tranform->setRotationZ(angle);
}

Vec3 Entity::GetRotation()
{
    return {
        tranform->getRotation().x, tranform->getRotation().x, tranform->getRotation().z
    };
}

void Entity::SetScale(Vec3 newScale)
{
    tranform->setLocalScale(newScale);
}

Vec3 Entity::GetScale()
{
    return {
        tranform->getLocalPosition().x, tranform->getLocalPosition().x, tranform->getLocalPosition().z
    };
}

Vec3 Entity::GetPreviousPosition()
{
    return {
        tranform->getPreviousPosition().x, tranform->getPreviousPosition().x, tranform->getPreviousPosition().z
    };
}

void Entity::SetParent(Entity* newParent)
{
    tranform->setParent(newParent->tranform);
}

Renderer* Entity::GetRenderer()
{
    return renderer;
}
