
#include "renderer.h"

#include <glm/gtc/type_ptr.hpp>

#include "Globals/Vec4.h"
#include "Base Game/Engine.h"
#include "Base Game/Engine.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

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


    projection = glm::ortho(0.0f, window->getWidth(), 0.0f, window->getHeight(), 0.1f, 100.0f); // Orthograpic

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
    view = glm::lookAt(cameraPos, {0, 0, 0}, {0, 1, 0});


    ShaderProgramSource source = Shader::ParseShader("../res/shaders/BasicShader.shader", ShaderUsed::Shapes);
    shaderShape = Shader::CreateShader(source.vertexSource, source.fragmentSource);
    
  ShaderProgramSource  source2 = Shader::ParseShader("../res/shaders/TextureShader.shader", ShaderUsed::Sprites);
    shaderSprite = Shader::CreateShader(source2.vertexSource, source2.fragmentSource);
    
    glEnable(GL_BLEND); //Transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(shaderShape);
    glUseProgram(shaderSprite);
    cout << "Renderer Created" << endl;
}

Renderer::~Renderer()
{
    cout << "Renderer Deleted" << endl;
    glDeleteProgram(shaderShape);
    glDeleteProgram(shaderSprite);
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


void Renderer::SetWindow(Window* window) { GLFWW = window; }

void Renderer::Setbitfield(GLbitfield mask) { this->mask = mask; }

GLbitfield Renderer::Getbitfield() { return this->mask; }


void Renderer::CreateVecBuffer(float* positions, int* indices, int positionsSize, int indicesSize, int atribVertexSize,
                               unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positionsSize, positions, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indicesSize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, atribVertexSize, GL_FLOAT, GL_FALSE, atribVertexSize * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Renderer::CreateVecBuffer(float* positions, int* indices, int positionsSize, int indicesSize, int atribVertexSize,
                               unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, int atribColorSize,
                               int atribUVSize)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positionsSize, positions, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indicesSize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, atribVertexSize, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, atribColorSize, GL_FLOAT, GL_FALSE, 9 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, atribUVSize, GL_FLOAT, GL_FALSE, 9 * sizeof(float),
                          (void*)((7) * sizeof(float)));
    glEnableVertexAttribArray(2);
    
}

void Renderer::createTextureBinder( unsigned int& textureId, const char* imagePath)
{
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    int width, height, nrChannels;
    unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    if (nrChannels == 4) //dependiendo de los canales, va a usar para rgba o rgb, sino se rompe todo.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else if (nrChannels == 3)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 
    }
    else if (nrChannels == 2)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data);
    else if (nrChannels == 1)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
    if (data)
    {
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        std::cout << "Image couldn't be loaded.";
    }
        glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    
}
void Renderer::createTextureBinder( unsigned int& textureId, const char* imagePath,int& width, int& height)
{
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    int nrChannels;
    unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    if (nrChannels == 4) //dependiendo de los canales, va a usar para rgba o rgb, sino se rompe todo.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else if (nrChannels == 3)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 
    }
    else if (nrChannels == 2)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data);
    else if (nrChannels == 1)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
    if (data)
    {
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        std::cout << "Image couldnt be loaded.";
    }
        glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    
}

void Renderer::createTextureBinder( unsigned int& textureId, const char* imagePath,int& width, int& height,GLint textureWrapping)
{
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapping);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapping);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureWrapping);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureWrapping);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    int nrChannels;
    unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    if (nrChannels == 4) //dependiendo de los canales, va a usar para rgba o rgb, sino se rompe todo.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else if (nrChannels == 3)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 
    }
    else if (nrChannels == 2)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data);
    else if (nrChannels == 1)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
    if (data)
    {
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        std::cout << "Image couldnt be loaded.";
    }
        glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    
}

void Renderer::DrawEntity2D(unsigned int VAO, int sizeIndices, Vec4 color, glm::mat4x4 model) const
{
    glClearColor(0.2f, 0.4f, 1, 1); //TODO: pasar a otra funcion
    glUseProgram(shaderShape);
    unsigned int transformLoc = glGetUniformLocation(shaderShape, "transform");

   

    glm::mat4 PVM = projection * view * model;

    glUniformMatrix4fv(transformLoc, shaderShape, GL_FALSE, glm::value_ptr(PVM));


    Shader::SetVec4("colorTint", color.x, color.y, color.z, color.w, shaderShape);
    glBindVertexArray(VAO);
    // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, sizeIndices, GL_UNSIGNED_INT, 0);
}

void Renderer::DrawSprite2D(unsigned VAO, int sizeIndices, Vec4 color, glm::mat4x4 model, unsigned& texture) const
{
   
    glUseProgram(shaderSprite);
  
    
    unsigned int transformLoc = glGetUniformLocation(shaderSprite, "MVP");

    glm::mat4 PVM = projection * view * model;
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(PVM));
    
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D,texture);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(nullptr));
}
