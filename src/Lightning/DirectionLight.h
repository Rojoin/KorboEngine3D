#pragma once
#include <glm/vec3.hpp>

#include "imgui/imgui.h"

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
    void ImGuiDirLight()
    {
        // Create collapsible section for this material
        if (ImGui::CollapsingHeader("Global Lighting"))
        {
            ImGui::DragFloat3("Direction", &direction[0]);
            ImGui::ColorEdit3("Ambient", &ambient[0]);
            ImGui::ColorEdit3("Diffuse", &diffuse[0]);
            ImGui::ColorEdit3("Specular", &specular[0]);
   
        }
    }
};
