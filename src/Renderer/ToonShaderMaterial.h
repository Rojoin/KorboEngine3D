#pragma once
#include <glm/vec4.hpp>

class ToonShaderMaterial
{
public:
    glm::vec4 materialColor  = glm::vec4(1.0f);
    glm::vec4 ambientColor = glm::vec4(1.0f);
    glm::vec4 specularColor = glm::vec4(1.0f);
    glm::vec4 rimColor = glm::vec4(1.0f);
    float glossiness = 0.5f;
    float rimAmount = 0.2f;
    float rimThreshold = 0.2f;
    float lightIntensity = 0.5f;
    float fadeEndDistance = 0.2f;
    float fadeStartDistance = 1.0f;

    ToonShaderMaterial();
    ~ToonShaderMaterial();
    void RenderImGui(bool& isActive);
};
