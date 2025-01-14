#include "shader.h"

#include "Lightning/PointLight.h"
#include "Lightning/SpotLight.h"

Shader::Shader(const std::string& filePath) : m_filePath(filePath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader();
    m_RendererID = CreateShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
    cout << "Shader Deleted" << endl;
}

void Shader::bind()
{
    glUseProgram(m_RendererID);
}

void Shader::unBind()
{
    glUseProgram(0);
}

GLuint Shader::CompileShader(const GLuint type, const std::string& source)
{
    GLuint id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
        char* message = (char*)alloca(lenght * sizeof(char));
        // esto lo hace con alloca para asignarlo en el stack dinamicamente

        glGetShaderInfoLog(id, lenght, &lenght, message);

        cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader") << endl;
        cout << message << endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

void Shader::SetInt(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetFloat(const std::string& name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetVec2(const std::string& name, const glm::vec2& value)
{
    glUniform2f(GetUniformLocation(name), value.x, value.y);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value)
{
    glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::SetVec3(const std::string& name, float x, float y, float z)
{
    glUniform3f(GetUniformLocation(name), x, y, z);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value)
{
    glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::SetMat3(const std::string& name, const glm::mat3& value)
{
    glUniformMatrix3fv(GetUniformLocation(name), 1,GL_FALSE, &value[0][0]);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1,GL_FALSE, &value[0][0]);
}

void Shader::SetMaterial(const std::string& name, Material material)
{
    SetVec3(name + ".ambient", material.ambient);
    SetVec3(name + ".diffuse", material.diffuse);
    SetVec3(name + ".specular", material.specular);
    SetFloat(name + ".shininess", material.shininess);
}

void Shader::SetPointLight(const std::string& name, const DirectionLight value, glm::vec3& lightPos)
{
    SetVec3(name + ".ambient", value.ambient);
    SetVec3(name + ".diffuse", value.diffuse);
    SetVec3(name + ".specular", value.specular);
    SetVec3(name + ".position", lightPos);
}

void Shader::SetPointLight(const std::string& name, const DirectionLight* value, glm::vec3& lightPos)
{
    SetVec3(name + ".ambient", value->ambient);
    SetVec3(name + ".diffuse", value->diffuse);
    SetVec3(name + ".specular", value->specular);
    SetVec3(name + ".position", lightPos);
}

void Shader::SetPointLight(const std::string& name, const PointLight* value)
{
    SetVec3(name + ".ambient", value->ambient);
    SetVec3(name + ".diffuse", value->diffuse);
    SetVec3(name + ".specular", value->specular);
    SetVec3(name + ".position", value->position);
    SetFloat(name + ".linear", value->linear);
    SetFloat(name + ".constant", value->constant);
}

void Shader::SetPointLight(const std::string& name, const PointLight value)
{
    SetVec3(name + ".ambient", value.ambient);
    SetVec3(name + ".diffuse", value.diffuse);
    SetVec3(name + ".specular", value.specular);
    SetVec3(name + ".position", value.position);
    SetFloat(name + ".linear", value.linear);
    SetFloat(name + ".constant", value.constant);
}

void Shader::SetDirectionalLight(const std::string& name, const DirectionLight* value)
{
    SetVec3(name + ".ambient", value->ambient);
    SetVec3(name + ".diffuse", value->diffuse);
    SetVec3(name + ".specular", value->specular);
    SetVec3(name + ".direction", value->direction);
}

void Shader::SetSpotLight(const std::string& name, const SpotLight* value)
{
    SetVec3(name + ".position", value->position);
    SetVec3(name + ".direction", value->direction);
    SetVec3(name + ".ambient", value->ambient);
    SetVec3(name + ".diffuse", value->diffuse);
    SetVec3(name + ".specular", value->specular);
    SetFloat(name + ".constant", value->constant);
    SetFloat(name + ".linear", value->linear);
    SetFloat(name + ".quadratic", value->quadratic);
    SetFloat(name + ".cutOff", value->cutOff);
    SetFloat(name + ".outerCutOff", value->outerCutOff);
}
void Shader::SetSpotLight(const std::string& name, const SpotLight value)
{
    SetVec3(name + ".position", value.position);
    SetVec3(name + ".direction", value.direction);
    SetVec3(name + ".ambient", value.ambient);
    SetVec3(name + ".diffuse", value.diffuse);
    SetVec3(name + ".specular", value.specular);
    SetFloat(name + ".constant", value.constant);
    SetFloat(name + ".linear", value.linear);
    SetFloat(name + ".quadratic", value.quadratic);
    SetFloat(name + ".cutOff", value.cutOff);
    SetFloat(name + ".outerCutOff", value.outerCutOff);
}

void Shader::SetDirectionalLight(const std::string& name, const DirectionLight value)
{
    SetVec3(name + ".ambient", value.ambient);
    SetVec3(name + ".diffuse", value.diffuse);
    SetVec3(name + ".specular", value.specular);
    SetVec3(name + ".direction", value.direction);
}


GLint Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    {
        return m_UniformLocationCache[name];
    }
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    m_UniformLocationCache[name] = location;
    return location;
}


int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentshader)
{
    GLuint program = glCreateProgram(); // unsigned int of GL
    GLuint vertex_S = CompileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fragment_S = CompileShader(GL_FRAGMENT_SHADER, fragmentshader);

    //Link shaders to program
    glAttachShader(program, vertex_S);
    glAttachShader(program, fragment_S);
    glLinkProgram(program);
    glValidateProgram(program);

    //Deleted because they are already linked to the program
    glDeleteShader(vertex_S);
    glDeleteShader(fragment_S);

    return program;
}

ShaderProgramSource Shader::ParseShader()
{
    ifstream inputStream(m_filePath);
    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    string line;
    stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    try
    {
        if (inputStream.is_open())
        {
            while (getline(inputStream, line))
            {
                if (line.find("#shader") != std::string::npos)
                {
                    if (line.find("vertex") != std::string::npos)
                        type = ShaderType::VERTEX;
                    else if (line.find("fragment") != std::string::npos)
                        type = ShaderType::FRAGMENT;
                }
                else
                {
                    ss[(int)type] << line << '\n';
                }
            }
        }
        else
        {
            //
        }
    }
    catch (ios::failure& exception)
    {
        std::cout << endl << "Couldnt Load Shader." << endl;
    }


    return {ss[0].str(), ss[1].str()};
}
