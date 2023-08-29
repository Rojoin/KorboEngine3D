#include "Entity.h"

#include "Renderer/renderer.h"

void Entity2D::Draw() const
{
    float vertexPos[maxVertices * 2];
    int counter = 0;
    for (int i = 0; i < maxVertices * 2; i + 2)
    {
        vertexPos[i] = vertex[counter].pos.x;
        vertexPos[i + 1] = vertex[counter].pos.y;
        counter++;
    }
}
