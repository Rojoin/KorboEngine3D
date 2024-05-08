#pragma once
#include <glm/vec3.hpp>

struct PointLight
{
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant;
    float linear;

    PointLight( glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float con, float lin)
    {
        position = pos;
        ambient = amb;
        diffuse = diff;
        specular = spec;
        constant = con;
        linear = lin;
    }
    PointLight( glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec)
    {
        position = pos;
        ambient = amb;
        diffuse = diff;
        specular = spec;
        constant = 0.09f;
        linear = 0.032f;
    }
    PointLight(): position(glm::vec3(0)), ambient(glm::vec3(1)), diffuse(glm::vec3(1)), specular(glm::vec3(01)), constant(0.09f), linear(0.032f)
    {
    }

    void setDir(const glm::vec3& pos)
    {
        position = pos;
    }
};
