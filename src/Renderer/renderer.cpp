#include "renderer.h"
#include "Vertex/vertex.h"

static GLuint CompileShader(const GLuint type, const std::string& source)
{
    GLuint id = glCreateShader(GL_VERTEX_SHADER);
    const char* src = source.c_str();
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);

    //TODO: Check for error handling system
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
    Vertex vertex[3] = {Vertex::Vertex(), Vertex::Vertex(), Vertex::Vertex()};

    vertex[0].pos = {-0.5f, 0.5f};
    vertex[1].pos = {0.0f, 0.5f};
    vertex[2].pos = {0.5f, -0.5f};

    unsigned int buffer; // Id of the generated buffer
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vertex), vertex,GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2,GL_FLOAT,GL_FALSE, 2 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Renderer::~Renderer()
{
    cout << "Renderer Deleted" << endl;
}

void Renderer::RenderScreen()
{
    /* Render here */
    glClear(mask);


    /* Swap front and back buffers */
    glfwSwapBuffers(GLFWW->getWindow());

    /* Poll for and process events */
    glfwPollEvents();
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
