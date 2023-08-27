#include <fstream>
#include <string>
#include <sstream>
#include "renderer.h"
#include "Vertex/vertex.h"

struct ShaderProgramSource
{
    string vertexSource;
    string fragmentSource;
};

static GLuint CompileShader(const GLuint type, const std::string& source)
{
    GLuint id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id,GL_COMPILE_STATUS,&result);

    if (result == GL_FALSE) 
    {

        int lenght;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&lenght);
        char* message = (char*)alloca(lenght * sizeof(char)); // esto lo hace con alloca para asignarlo en el stack dinamicamente

        glGetShaderInfoLog(id,lenght,&lenght, message);

        cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader") << endl;
        cout << message << endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

static int CreateShader(const std::string& vertexShader, const std::string& fragmentshader)
{
    GLuint program = glCreateProgram(); // unsigned int of GL
    GLuint vertex_S = CompileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fragment_S = CompileShader(GL_FRAGMENT_SHADER, fragmentshader);

    //Link shaders to program
    glAttachShader(program,vertex_S);
    glAttachShader(program,fragment_S);
    glLinkProgram(program);
   
    
    glValidateProgram(program);
    
    //Deleted because they are already linked to the program
    glDeleteShader(vertex_S);
    glDeleteShader(fragment_S);
    
    return program;
}

static ShaderProgramSource ParseShader(const string& filepath)
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

    while (getline(inputStream,line))
    {
        if (line.find("#shader") != std::string::npos) 
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str() , ss[1].str() };
}

Renderer::Renderer(Window* window, GLbitfield mask)
{
    this->GLFWW = window;
    this->mask = mask;
    cout << "Renderer Created" << endl;
}

Renderer::Renderer(Window* window)
{
    this->GLFWW = window;
    this->mask = GL_COLOR_BUFFER_BIT;
    cout << "Renderer Created" << endl;
    //Vertex vertex[3] = {Vertex::Vertex(), Vertex::Vertex(), Vertex::Vertex()};
    //
    //vertex[0].pos = {-0.5f, 0.5f};
    //vertex[1].pos = {0.0f, 0.5f};
    //vertex[2].pos = {0.5f, -0.5f};

    float positions[6] =
    {
       -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    unsigned int buffer; // Id of the generated buffer
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(vertex), vertex,GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions,GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2,GL_FLOAT,GL_FALSE,sizeof(float) * 2, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    ShaderProgramSource source = ParseShader("../res/shaders/BasicShader.shader");
    GLuint shader = CreateShader(source.vertexSource, source.fragmentSource);

    glUseProgram(shader);
}

Renderer::~Renderer()
{
    cout << "Renderer Deleted" << endl;
}

void Renderer::RenderScreen()
{
    /* Render here */
    glClear(mask);

    glDrawArrays(GL_TRIANGLES,0,3);

    /* Swap front and back buffers */
    glfwSwapBuffers(GLFWW->getWindow());

    /* Poll for and process events */
    glfwPollEvents();

    // Cuando se termina el loop tenemos que usar el glDeleteProgram(shader)
}

void Renderer::SetWindow(Window* window)
{
    GLFWW = window;
}

void Renderer::Setbitfield(GLbitfield mask)
{
    this->mask = mask;
}

GLbitfield Renderer::Getbitfield()
{
    return this->mask;
}
