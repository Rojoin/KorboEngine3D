#pragma once


class Entity;

class Component
{
public :
    explicit Component(Entity* entity);
    virtual ~Component() = 0;

protected:
    Entity* entity;
};
