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
    Draw();
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

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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


unsigned int Renderer::CreateVecBuffer(float positions[],unsigned int indices[], int positionsSize, int indicesSize)
{
    unsigned int buffer;
    glGenBuffers(1, &buffer);

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, positionsSize, positions,GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2,GL_FLOAT,GL_FALSE, sizeof(float) * 2, 0);
    
    unsigned int ibo; // Id of the generated buffer
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices,GL_STATIC_DRAW);
    return buffer;
}

void Renderer::Draw(float positions[], float indices[], unsigned int& buffer)
{
    
    
}

void Renderer::Draw()
{
    float positions[] =
    {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f
    };
    unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };
    
    unsigned int buffer = CreateVecBuffer(positions, indices, sizeof(float) * 8, sizeof(float) *6);;

}
