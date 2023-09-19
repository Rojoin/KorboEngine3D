#include "renderer.h"

#include <glm/gtc/type_ptr.hpp>

#include "Globals/Vec4.h"

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

    ShaderProgramSource source = shader.ParseShader("../res/shaders/BasicShader.shader");
    shaderProgram = shader.CreateShader(source.vertexSource, source.fragmentSource);
    glEnable(GL_BLEND);//Transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(shaderProgram);
    cout << "Renderer Created" << endl;
}

Renderer::~Renderer()
{
    cout << "Renderer Deleted" << endl;
    glDeleteProgram(shaderProgram);
}

void Renderer::DeleteObjects(unsigned& VAO, unsigned& VBO, unsigned& EBO)
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Renderer::EndDrawing()
{
    /* Swap front and back buffers */
    glfwSwapBuffers(GLFWW->getWindow());

    /* Poll for and process events */
    glfwPollEvents();
}

void Renderer::BeginDrawing()
{
    /* Render here */
    glClear(mask);
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


void Renderer::CreateVecBuffer(float* positions,  int* indices, int positionsSize, int indicesSize, int atribVertexSize, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
   
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)* positionsSize, positions, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float)* indicesSize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, atribVertexSize, GL_FLOAT, GL_FALSE, atribVertexSize * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 
   
}

void Renderer::DrawEntity2D(unsigned int VAO,int sizeIndices, Vec4 color, glm::mat4x4 trans) const
{
    glClearColor(0.2f,0.4f,1,1);
    glUseProgram(shaderProgram);
    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    Shader::SetVec4("colorTint",color.x,color.y,color.z,color.w,shaderProgram);
    //TODO: CAMBIAR ESTO A FUNCIONES Y AGREGAR EL MODEL VIEW A ESTO
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, sizeIndices, GL_UNSIGNED_INT, 0);

}


