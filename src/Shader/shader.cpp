#include "shader.h"

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
