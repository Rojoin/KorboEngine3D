#include "Sprite.h"

Sprite::Sprite(Renderer* renderer,Vec4 color, Vec3 position, Vec3 newScale,const char* imagePath, int width, int height): Entity2D(
    renderer, position, newScale)
{
    vertexSize = 36;
    //Reads clockwise
    //If diferent use glFrontFace(GL_CCW) (Graphics 2)
//TODO CAMBIAR TODO A VERTICES
    vertexPositions = new float[36]{
        // positions          // colors                         // texture coords
        0.5f,  0.5f, 0.0f,   1.0f,1.0f,1.0f,1.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   1.0f,1.0f,1.0f,1.0f,   1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f,   1.0f,1.0f,1.0f,1.0f,   0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f,1.0f,1.0f,1.0f,   0.0f, 1.0f  // top left 
   };
    
    indexSize = 6;
    indices = new int[indexSize]{
        0, 1, 3,
        1, 2, 3
    };
    this->color = color;
    renderer->CreateVecBuffer(vertexPositions, indices, vertexSize, indexSize, atribPosSize, VAO, VBO, EBO,atribColorSize,atribUVSize);
    renderer->createTextureBinder(textureId, imagePath);
    std::cout << "Sprite Created" <<endl;
}

void Sprite::Draw()
{
   renderer->DrawSprite2D(VAO,indexSize,color,model,textureId);
}

Sprite::~Sprite()
{
    glDeleteBuffers(1, &textureId);
}
