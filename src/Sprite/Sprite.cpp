#include "Sprite.h"

Sprite::Sprite(Renderer* renderer,Vec4 color, Vec3 position, Vec3 newScale, string imagePath, int width, int height): Shape(
    renderer, position, newScale)
{
    vertexSize = 24;
    //Reads clockwise
    //If diferent use glFrontFace(GL_CCW) (Graphics 2)
//TODO CAMBIAR TODO A VERTICES
    vertexPositions = new float[32]{
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
   };
    
    indexSize = 6;
    indices = new int[indexSize]{
        0, 1, 3,
        1, 2, 3
    };
    this->color = color;
    renderer->CreateVecBuffer(vertexPositions, indices, vertexSize, indexSize, atribVertexSize, VAO, VBO, EBO);
    renderer->createTextureBinder(uvPositions, uvSize, textureId, imagePath, width, height, nrChannels);
}

void Sprite::Draw()
{
   renderer->DrawEntity2D(VAO,indexSize,color,model,textureId);
}

Sprite::~Sprite()
{
    glDeleteBuffers(1, &textureId);
}
