#include "Pyramid.h"

Pyramid::Pyramid(Renderer* renderer, Vec3 position, Vec3 newScale) : Entity3D(renderer, position, newScale)
{
    vertexSize = 15;
    vertexPositions = new float[vertexSize]{
        0.5f, -0.5f, 0.5f, // bottom right
        -0.5f, -0.5f, 0.5f, // bottom left
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        0.0f, 0.5f, 0.0f
    };
    indexSize = 18;
    indices = new int[indexSize]{
        0, 1, 3,
        1, 2, 3,
        4, 0, 1,
        4, 0, 2,
        4, 2, 3,
        4, 3, 1
    };
    this->color = {1, 1, 1, 1};
    renderer->createVecBuffer(vertexPositions, indices, vertexSize, indexSize, atribPosSize, VAO, VBO, EBO);;
}
Pyramid::Pyramid(Renderer* renderer, Vec3 position, Vec3 newScale, Vec4 color) : Entity3D(renderer, position, newScale)
{
    vertexSize = 15;
    vertexPositions = new float[vertexSize]{
        0.5f, -0.5f, 0.5f, // bottom right
        -0.5f, -0.5f, 0.5f, // bottom left
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        0.0f, 0.5f, 0.0f
    };
    indexSize = 18;
    indices = new int[indexSize]{
        0, 1, 3,
        1, 2, 3,
        4, 0, 1,
        4, 0, 2,
        4, 2, 3,
        4, 3, 1
    };
    this->color = {color.x, color.y, color.z, color.w};
    renderer->createVecBuffer(vertexPositions, indices, vertexSize, indexSize, atribPosSize, VAO, VBO, EBO);;
}
