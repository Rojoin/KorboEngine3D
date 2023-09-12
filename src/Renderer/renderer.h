#pragma once
#include "Globals/dllHeader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Window/window.h"

#include "Vertex/vertex.h"
#include "Shader/shader.h"

using namespace std;

class EXPORT Renderer
{
public:
    Renderer(Window* window);
    Renderer(Window* window, GLbitfield mask);
    ~Renderer();
    void DeleteObjects(unsigned int& VAO,unsigned int& VBO, unsigned int& EBO);
    void EndDrawing();
    void BeginDrawing();
    void SetWindow(Window* window);
    void Setbitfield(GLbitfield mask);
    GLbitfield Getbitfield();
    void CreateVecBuffer(float* positions,  int* indices, int positionsSize, int indicesSize, int atribVertexSize,
                         unsigned int& VAO,
                         unsigned int& VBO, unsigned int& EBO);
    void DrawEntity2D(unsigned int VAO, int sizeIndices);


private:
    Window* GLFWW;
    GLbitfield mask;
    Shader shader;
    GLuint shaderProgram;
};
