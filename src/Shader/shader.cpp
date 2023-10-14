#include "shader.h"

Shader::Shader()
{
    cout << "Shader Created" << endl;
}

Shader::~Shader()
{
    cout << "Shader Deleted" << endl;
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

ShaderProgramSource Shader::ParseShader(const string& filepath,ShaderUsed shaderUsed)
{
    ifstream inputStream(filepath);
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
        std::cout << endl << "Couldnt Load Shader, using default one." << endl;
        if (shaderUsed == ShaderUsed::Shapes)
        {
            string vertexShader = R"(#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 transform;

void main()
{
	gl_Position = transform * position;
};
)";
            string fragmentShader = R"(#version 330 core

layout(location = 0) out vec4 color;
uniform vec4 colorTint;

void main()
{
   color = vec4(colorTint.x,colorTint.y,colorTint.z,colorTint.w);
};)";

            return {vertexShader, fragmentShader};
        }
        else if (shaderUsed == ShaderUsed::Sprites)
        {
            string vertexShader = R"(#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 MVP;

out vec4 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = MVP * position;
    ourColor = aColor;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
};
)";
            string fragmentShader = R"(#version 330 core

out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
})";

            return {vertexShader, fragmentShader};
        }
    }


    return {ss[0].str(), ss[1].str()};
}
