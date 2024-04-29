#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "GL/glew.h"

#include <unordered_map>
#include <glm/glm.hpp>

#include "Material.h"
#include "Lightning/DirectionLight.h"
#include "Lightning/SpotLight.h"

using namespace std;

struct ShaderProgramSource
{
    string vertexSource;
    string fragmentSource;
};

enum class ShaderUsed
{
    Shapes,
    Sprites
};


class Shader
{
public:
    Shader(const std::string& filePath);
    ~Shader();
    void bind();
    void unBind();
    ShaderProgramSource ParseShader();
    int CreateShader(const std::string& vertexShader, const std::string& fragmentshader);
    GLuint CompileShader(const GLuint type, const std::string& source);
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);
    void SetVec2(const std::string& name, const glm::vec2& value);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetVec3(const std::string& name, float x, float y, float z);
    void SetVec4(const std::string& name, const glm::vec4& value);
    void SetMat3(const std::string& name, const glm::mat3& value);
    void SetMat4(const std::string& name, const glm::mat4& value);
    void SetMaterial(const std::string& name, Material material);
    void SetLight(const std::string& name, const DirectionLight value, glm::vec3& lightPos);
    void SetLight(const std::string& name, const DirectionLight* value, glm::vec3& lightPos);
    void SetDirectionalLight(const std::string& name, const DirectionLight* value);
    void SetSpotLight(const std::string& name, const SpotLight* value);
    void SetSpotLight(const std::string& name, SpotLight value);
    void SetDirectionalLight(const std::string& name, DirectionLight value);
    void SetLight(const std::string& name, const DirectionLight* value);
    void SetLight(const std::string& name, DirectionLight value);

private:
    std::string m_filePath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, GLint> m_UniformLocationCache;
    GLint GetUniformLocation(const std::string& name);
};
