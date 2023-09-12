#include "Triangle.h"

Triangle::Triangle(Renderer* renderer) : Shape(renderer)
{
    vertexSize = 9;
    //Reads clockwise
    //If diferent use glFrontFace(GL_CCW) (Graphics 2)
    vertexPositions = new float[vertexSize]
    {
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    indexSize = 3;
    indices = new int[indexSize]
    {
        0, 1, 2
    };
    this->color = {1,1,1,1};
    renderer->CreateVecBuffer(vertexPositions, indices, vertexSize, indexSize, atribVertexSize, VAO, VBO, EBO);
}

Triangle::Triangle(Renderer* renderer,Vec4 color) : Shape(renderer)
{
    vertexSize = 9;
    //Reads clockwise
    //If diferent use glFrontFace(GL_CCW) (Graphics 2)
    vertexPositions = new float[vertexSize]
    {
        0.0f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f
   };
    indexSize = 3;
    indices = new int[indexSize]
    {
        0, 1, 2
    };
    this->color = color;
    renderer->CreateVecBuffer(vertexPositions, indices, vertexSize, indexSize, atribVertexSize, VAO, VBO, EBO);
}
