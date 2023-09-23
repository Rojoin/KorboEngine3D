#include "Square.h"

Square::Square(Renderer* renderer) : Shape(renderer)
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
    indexSize = 6;
    indices = new int[indexSize]{
        0, 1, 3,
        1, 2, 3
    };
    this->color = {1,1,1,1};
    renderer->CreateVecBuffer(vertexPositions, indices, vertexSize, indexSize, atribVertexSize, VAO, VBO, EBO);
}

Square::Square(Renderer* renderer,Vec4 color) : Shape(renderer)
{
    vertexSize = 12;
    //Reads clockwise
    //If diferent use glFrontFace(GL_CCW) (Graphics 2)
    vertexPositions = new float[12]{
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f
    };
    indexSize = 6;
    indices = new int[indexSize]{
        0, 1, 3,
        1, 2, 3
    };
    this->color = color;
    renderer->CreateVecBuffer(vertexPositions, indices, vertexSize, indexSize, atribVertexSize, VAO, VBO, EBO);
}
