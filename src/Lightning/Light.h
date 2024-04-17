#pragma once
#include <glm/vec3.hpp>

struct Light
{
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    Light()
    {
        ambient = glm::vec3(0.2f, 0.2f, 0.2f);
        diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
        specular = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    Light(glm::vec3 amb, glm::vec3 dif, glm::vec3 spec)
    {
        ambient = amb;
        diffuse = dif;
        specular = spec;
    }

    Light(glm::vec3 pos, glm::vec3 amb, glm::vec3 dif, glm::vec3 spec)
    {
        position = pos;
        ambient = amb;
        diffuse = dif;
        specular = spec;
    }
};
