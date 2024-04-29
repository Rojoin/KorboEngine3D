#pragma once
#include <glm/trigonometric.hpp>
#include <glm/vec3.hpp>


struct SpotLight
{
public:
    glm::vec3 direction;
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;

    SpotLight(glm::vec3 dir, glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float con, float lin,
              float quadra, float cut, float outerCut)
    {
        direction = dir;
        position = pos;
        ambient = amb;
        diffuse = diff;
        specular = spec;
        constant = con;
        linear = lin;
        quadratic = quadra;
        cutOff = cut;
        outerCutOff = outerCut;
    }

    SpotLight(): direction(glm::vec3(0)), position(glm::vec3(0)), ambient(glm::vec3(0.0f, 0.0f, 0.0f)),
                 diffuse(glm::vec3(1.0f, 1.0f, 1.0f)), specular(glm::vec3(1.0f, 1.0f, 1.0f)), constant(1.0f),
                 linear(0.09f), quadratic(0.032f),
                 cutOff(glm::cos(glm::radians(12.5f))),
                 outerCutOff(glm::cos(glm::radians(15.0f)))
    {
    }

    void setDirAndPos(const glm::vec3& dir, const glm::vec3& pos)
    {
        direction = dir;
        position = pos;
    }
};
