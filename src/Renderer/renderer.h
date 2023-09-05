#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Window/window.h"

#include "Vertex/vertex.h"
#include "Shader/shader.h"

using namespace std;

class Renderer
{
public:
    Renderer(Window* window);
    Renderer(Window* window, GLbitfield mask);
    ~Renderer();
    void RenderScreen();
    void SetWindow(Window* window);
    void Setbitfield(GLbitfield mask);
    GLbitfield Getbitfield();
    void Draw(Vertex vertex[], float maxVertices);
    void Draw();

private:
    Window* GLFWW;
    GLbitfield mask;
    Shader shader;
    GLuint shaderProgram;
};
