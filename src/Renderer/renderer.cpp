#include "renderer.h"

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
    //Vertex vertex[3] = {Vertex::Vertex(), Vertex::Vertex(), Vertex::Vertex()};
    //
    //vertex[0].pos = {-0.5f, 0.5f};
    //vertex[1].pos = {0.0f, 0.5f};
    //vertex[2].pos = {0.5f, -0.5f};

    //float positions[6] =
    //{
    //    -0.5f, -0.5f,
    //    0.0f, 0.5f,
    //    0.5f, -0.5f
    //};

    //unsigned int buffer; // Id of the generated buffer
    //glGenBuffers(1, &buffer);
    //glBindBuffer(GL_ARRAY_BUFFER, buffer);
    ////glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(vertex), vertex,GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions,GL_STATIC_DRAW);

    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 2,GL_FLOAT,GL_FALSE, sizeof(float) * 2, 0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    ShaderProgramSource source = shader.ParseShader("../res/shaders/BasicShader.shader");
    shaderProgram = shader.CreateShader(source.vertexSource, source.fragmentSource);

    glUseProgram(shaderProgram);
    cout << "Renderer Created" << endl;
}

Renderer::~Renderer()
{
    cout << "Renderer Deleted" << endl;
    glDeleteProgram(shaderProgram);
}

void Renderer::RenderScreen()
{
    /* Render here */
    glClear(mask);

    glDrawArrays(GL_TRIANGLES, 0, 3);

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

void Renderer::Draw(float vertexPos[], float maxVertices)
{
    unsigned int buffer; // Id of the generated buffer
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(vertex), vertex,GL_STATIC_DRAW);
    //  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions,GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, maxVertices * sizeof(float), vertexPos,GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2,GL_FLOAT,GL_FALSE, sizeof(float) * 2, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
