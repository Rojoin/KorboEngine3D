#pragma once
#include "Globals/dllHeader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/mat4x4.hpp>

#include "Globals/Vec4.h"
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
    void DeleteObjects(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
    void EndDrawing();
    void BeginDrawing();
    void SetWindow(Window* window);
    void Setbitfield(GLbitfield mask);
    GLbitfield Getbitfield();
    void CreateVecBuffer(float* positions, int* indices, int positionsSize, int indicesSize, int atribVertexSize,
                         unsigned int& VAO,
                         unsigned int& VBO, unsigned int& EBO);
    void CreateVecBuffer(float* positions, int* indices, int positionsSize, int indicesSize, int atribVertexSize,
                         unsigned& VAO, unsigned& VBO, unsigned& EBO, int atribColorSize, int atribUVSize);
    void createTextureBinder(unsigned& textureId, const char* imagePath);
    void createTextureBinder(unsigned& textureId, const char* imagePath, int& width, int& height);
    void createTextureBinder(unsigned& textureId, const char* imagePath, int& width, int& height,
                             GLint textureWrapping);
    void DrawEntity2D(unsigned VAO, int sizeIndices, Vec4 color, glm::mat4x4 model) const;
    void DrawSprite2D(unsigned int VAO, int sizeIndices, Vec4 color, glm::mat4x4 model, unsigned int& texture) const;

private:
    Window* GLFWW;
    GLbitfield mask;
    Shader shader;
    GLuint shaderShape;
    GLuint shaderSprite;
    glm::mat4x4 model;
    glm::mat4x4 view;
    glm::mat4x4 projection;
};
