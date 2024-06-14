#include "Entity.h"


//Todo: Add Entity with vector3
Entity::Entity(Renderer* renderer,glm::vec3 position,glm::vec3 rotation,glm::vec3 scale)
{
    cout << "Init Entity";
    tranform = new Transform(this,position,rotation,scale);
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
    tranform->SetPosition(newPosition);
}

void Entity::SetPosition(glm::vec3 newPosition)
{
    tranform->SetPosition(newPosition);
}

void Entity::SetPreviousPosition()
{
    tranform->SetPreviousPosition();
}

void Entity::MovePosition(Vec3 newPosition)
{
    tranform->MovePosition(newPosition);
}

void Entity::MovePosition(glm::vec3 newPosition)
{
    tranform->MovePosition(newPosition);
}

Vec3 Entity::GetPosition()
{
   return { tranform->GetPosition().x, tranform->GetPosition().y, tranform->GetPosition().z};
}

void Entity::SetRotationX(float angle)
{
    tranform->SetRotationX(angle);
}

void Entity::SetRotationY(float angle)
{
    tranform->SetRotationX(angle);
}

void Entity::SetRotationZ(float angle)
{
    tranform->SetRotationX(angle);
}

Vec3 Entity::GetRotation()
{
    return {
        tranform->GetRotation().x, tranform->GetRotation().x, tranform->GetRotation().z
    };
}

void Entity::SetScale(Vec3 newScale)
{
    tranform->SetScale(newScale);
}

Vec3 Entity::GetScale()
{
    return {
        tranform->GetScale().x, tranform->GetScale().x, tranform->GetScale().z
    };
}

Vec3 Entity::GetPreviousPosition()
{
    return {
        tranform->GetPreviousPosition().x, tranform->GetPreviousPosition().x, tranform->GetPreviousPosition().z
    };
}
