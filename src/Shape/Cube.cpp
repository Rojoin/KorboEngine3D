#include "Cube.h"

Cube::Cube(Renderer* renderer, Vec3 position, Vec3 newScale) : Entity3D(renderer, position, newScale)
{
    vertexSize = 24;
    vertexPositions = new float[vertexSize]{
        0.5f, 0.5f, 0.5f, // top right
        0.5f, -0.5f, 0.5f, // bottom right
        -0.5f, -0.5f, 0.5f, // bottom left
        -0.5f, 0.5f, 0.5f, // top Left
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f
    };
    indexSize = 36;
    indices = new int[indexSize]{
        0, 1, 3,
        1, 2, 3,
        4, 5, 7,
        5, 6, 7,
        0, 3, 4,
        3, 4, 7,
        1, 2, 5,
        2, 6, 5,
        1, 0, 5,
        0, 4, 5,
        3, 2, 6,
        3, 7, 6
    };
    this->color = {1,1,1,1};
    renderer->CreateVecBuffer(vertexPositions, indices, vertexSize, indexSize, atribPosSize, VAO, VBO, EBO);;
}

