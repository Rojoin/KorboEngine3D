#include "Sprite.h"

Sprite::Sprite(Renderer* renderer,Vec4 color, Vec3 position, Vec3 newScale, string imagePath, int width, int height): Shape(
    renderer, position, newScale)
{
    vertexSize = 12;
    //Reads clockwise
    //If diferent use glFrontFace(GL_CCW) (Graphics 2)
    vertexPositions = new float[12]{
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f
    };
    uvSize = 8;
    uvPositions = new float[8]{
        0.5f, 0.5f, // top right
        0.5f, -0.5f, // bottom right
        -0.5f, -0.5f, // bottom left
        -0.5f, 0.5f,
    };
    indexSize = 6;
    indices = new int[indexSize]{
        0, 1, 3,
        1, 2, 3
    };
    this->color = color;
    renderer->CreateVecBuffer(vertexPositions, indices, vertexSize, indexSize, atribVertexSize, VAO, VBO, EBO);
    renderer->createTextureBinder(uvPositions, uvSize, UVAO, imagePath, width, height, nrChannels);
}

void Sprite::Draw()
{
    Shape::Draw();
}

Sprite::~Sprite()
{
    glDeleteBuffers(1, &UVAO);
}
