#include "Triangle.h"

Triangle::Triangle(Renderer* renderer,Vec3 position, Vec3 newScale): Shape(renderer,position,newScale)
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
    renderer->CreateVecBuffer(vertexPositions, indices, vertexSize, indexSize, atribPosSize, VAO, VBO, EBO);
}

Triangle::Triangle(Renderer* renderer,Vec4 color,Vec3 position, Vec3 newScale) : Shape(renderer,position,newScale)
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
    renderer->CreateVecBuffer(vertexPositions, indices, vertexSize, indexSize, atribPosSize, VAO, VBO, EBO);
}
