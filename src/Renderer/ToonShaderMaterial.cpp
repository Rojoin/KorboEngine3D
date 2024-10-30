#include "ToonShaderMaterial.h"
#pragma once
#include "imgui.h"

ToonShaderMaterial::ToonShaderMaterial()
{
}

ToonShaderMaterial::~ToonShaderMaterial()
{
}

void ToonShaderMaterial::RenderImGui(bool& isActive)
{
    // Create collapsible section for this material
    if (ImGui::CollapsingHeader("Toon Shader Material"))
    {
        ImGui::Checkbox("Active Shader", &isActive);
        ImGui::ColorEdit4("Material Color", &materialColor[0]);
        ImGui::ColorEdit4("Ambient Color", &ambientColor[0]);
        ImGui::ColorEdit4("Specular Color", &specularColor[0]);
        ImGui::ColorEdit4("Rim Color", &rimColor[0]);

        ImGui::SliderFloat("Glossiness", &glossiness, 0.0f, 1.0f);
        ImGui::SliderFloat("Rim Amount", &rimAmount, 0.0f, 1.0f);
        ImGui::SliderFloat("Rim Threshold", &rimThreshold, 0.0f, 1.0f);
    }
}
