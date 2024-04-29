#pragma once
#include <glm/vec3.hpp>

struct DirectionLight
{
    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    DirectionLight()
    {
        ambient = glm::vec3(0.2f, 0.2f, 0.2f);
        diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
        specular = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    DirectionLight(glm::vec3 amb, glm::vec3 dif, glm::vec3 spec)
    {
        ambient = amb;
        diffuse = dif;
        specular = spec;
    }

    DirectionLight(glm::vec3 dir, glm::vec3 amb, glm::vec3 dif, glm::vec3 spec)
    {
        direction = dir;
        ambient = amb;
        diffuse = dif;
        specular = spec;
    }
};
