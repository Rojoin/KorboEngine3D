#pragma once


class Entity;

class Component
{
public :
    explicit Component(Entity* entity);

protected:
    Entity* entity = nullptr;
};
