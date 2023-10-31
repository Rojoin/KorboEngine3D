#include "Sprite.h"

#include "Animation/Animation.h"
#include "Animation/Animation.h"

Sprite::Sprite(Renderer* renderer, Vec4 color, Vec3 position, Vec3 newScale, const char* imagePath): Entity2D(
    renderer, position, newScale)
{
    vertexSize = 36;
    //Reads clockwise
    //If diferent use glFrontFace(GL_CCW) (Graphics 2)

    vertexPositions = new float[36]{
        // positions          // colors             // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f // top left 
    };
    //Crear clase Animation
    //En sprite tengo un puntero a animation, sino esta null
    //A animation le paso el vertexPositions para que toque los uvs
    //Crear animator? 

    indexSize = 6;
    indices = new int[indexSize]{
        0, 1, 3,
        1, 2, 3
    };
    this->color = color;
    renderer->CreateVecBuffer(vertexPositions, indices, vertexSize, indexSize, atribPosSize, VAO, VBO, EBO,
                              atribColorSize, atribUVSize);
    renderer->createTextureBinder(textureId, imagePath, this->width, this->height);
    std::cout << "Sprite Created" << endl;
    animation = Animation();
}

int Sprite::getWidth()
{
    return width;
}

int Sprite::getHeight()
{
    return height;
}

void Sprite::Draw()
{
    renderer->DrawSprite2D(VAO, indexSize, color, model, textureId);
}

Sprite::~Sprite()
{
    glDeleteBuffers(1, &textureId);
}

void Sprite::ChangeAnimation(Animation animation)
{
    this->animation = animation;
}

void Sprite::UpdateAnimation()
{
    if (animation.hasFrames())
    {
        int numberOfUVS = 4;
        int strife = 7;
        for (int i = 0; i < numberOfUVS; ++i)
        {
            ChangeUVCoord(strife * (i+1), animation.currentFrame.getUVCoord(i));
        }
    }
}

void Sprite::ChangeUVCoord(int strife, glm::vec2 UVS)
{
    vertexPositions[strife] = UVS.x;
    vertexPositions[strife + 1] = UVS.y;
}
