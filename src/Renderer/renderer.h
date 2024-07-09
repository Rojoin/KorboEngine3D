#pragma once
#include "Globals/dllHeader.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/mat4x4.hpp>

#include "Camera/Camera.h"


#include "Globals/Vec4.h"
#include "Mesh/BasicMesh.h"
#include "Shader/Material.h"
#include "Window/window.h"

#include "Vertex/vertex.h"
#include "Shader/shader.h"

using namespace std;



class EXPORT Renderer
{
public:
    float ambientStrengh;
    unsigned textureDefault;
    DirectionLight* globalLight;
    PointLight* pointLight;
    SpotLight* flashLight;
    glm::mat4x4 projection;
    glm::mat4x4 view;
    glm::vec3 lightPos;
    Renderer(Window* window, Camera* mainCamera);
    Renderer(Window* window, GLbitfield mask);
    ~Renderer();
    void DeleteObjects(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
    void EndDrawing();
    void BeginDrawing();
    void SetWindow(Window* window);
    void Setbitfield(GLbitfield mask);
    GLbitfield Getbitfield();
    void createVecBuffer(float* positions, int* indices, int positionsSize, int indicesSize, int atribVertexSize,
                         unsigned int& VAO,
                         unsigned int& VBO, unsigned int& EBO);
    void createVecBufferWithNormals(float* positions, int* indices, int positionsSize, int atribNormalSize,
                                    int atribVertexSize, int indicesSize, unsigned& VAO, unsigned& VBO, unsigned& EBO);
    void createVecBufferWithNormalsUV(float* positions, int* indices, int positionsSize, int atribNormalSize,
                                      int atribVertexSize, int indicesSize, int atribUVSize, unsigned& VAO,
                                      unsigned& VBO,
                                      unsigned& EBO);
    void createVecBufferWithUV(float* positions, int* indices, int positionsSize, int indicesSize, int atribVertexSize,
                               unsigned& VAO, unsigned& VBO, unsigned& EBO, int atribColorSize, int atribUVSize);
    void createTextureBinder(unsigned& textureId, const char* imagePath);
    void createTextureBinder(unsigned& textureId, const char* imagePath, int& width, int& height);
    void createTextureBinder(unsigned& textureId, const char* imagePath, int& width, int& height,
                             GLint textureWrapping);
    void DrawEntity(unsigned VAO, int sizeIndices, Vec4 color, glm::mat4x4 model) const;
    void DrawSprite2D(unsigned int VAO, int sizeIndices, Vec4 color, glm::mat4x4 model, unsigned int& texture) const;
    void DrawEntity3D(unsigned VAO, int sizeIndices, ::Vec4 color, glm::mat4x4 model, Material material,
                      unsigned& texture, bool
                      isUsingTexture);
    void DrawModel3D( glm::mat4x4 model, unsigned VAO, std::vector<unsigned int> indices,
                     std::vector<Texture> textures);
    void DrawLinesAABB(glm::mat4x4 model, std::vector<glm::vec3> vertices);
    Shader* shaderBasicModel;
    Shader* shaderLines;

private:
    Window* GLFWW;
    GLbitfield mask;
    Shader* shaderShape;
    Shader* shaderSprite;
    Shader* shaderLightning;
    glm::mat4x4 model;
    Camera* camera;
};
