#include "Sprite.h"

#include "Animation/Animation.h"


Sprite::Sprite(Renderer* renderer, Vec4 color, Vec3 position,Vec3 newScale, const char* imagePath): Entity2D(
    renderer, position, newScale)
{
    vertexSize = 36;
    //Reads clockwise
    //If diferent use glFrontFace(GL_CCW) (Graphics 2)

    vertexPositions = new float[36]{
        // positions            // colors          // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f // top left 
    };

    indexSize = 6;
    indices = new int[indexSize]{
        0, 1, 3,
        1, 2, 3
    };
    this->color = color;
    renderer->createVecBufferWithUV(vertexPositions, indices, vertexSize, indexSize, atribPosSize, VAO, VBO, EBO,
                              atribColorSize, atribUVSize);
    renderer->createTextureBinder(textureId, imagePath, this->width, this->height);
    std::cout << "Sprite Created" << endl;
    animation = Animation();
}

Sprite::Sprite(Renderer* renderer, Vec4 color, Vec3 position, Vec3 newScale, const char* imagePath,
               GLint textureFilter): Entity2D(
    renderer, position, {0,0,0},newScale)
{
    vertexSize = 36;
    //Reads clockwise
    //If diferent use glFrontFace(GL_CCW) (Graphics 2)

    vertexPositions = new float[36]{
        // positions            // colors          // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f // top left 
    };


    indexSize = 6;
    indices = new int[indexSize]{
        0, 1, 3,
        1, 2, 3
    };
    this->color = color;
    renderer->createVecBufferWithUV(vertexPositions, indices, vertexSize, indexSize, atribPosSize, VAO, VBO, EBO,
                              atribColorSize, atribUVSize);
    renderer->createTextureBinder(textureId, imagePath, this->width, this->height, textureFilter);
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
    renderer->DrawSprite2D(VAO, indexSize, color, this->tranform->modelWorld, textureId);
}

Sprite::~Sprite()
{
    glDeleteBuffers(1, &textureId);
}

void Sprite::ChangeAnimation(Animation animation)
{
    if (this->animation == animation)
        return;
    
    this->animation = animation;
}

void Sprite::ChangeAnimation()
{
    this->animation = Animation();
}

void Sprite::UpdateAnimation()
{
    if (animation.hasFrames())
    {
        animation.update();
        int numberOfUVS = 4;
        int strife = 7;
        int row = 9;
        for (int i = 0; i < numberOfUVS; ++i)
        {
            ChangeUVCoord(strife + (i * row), animation.currentFrame->getUVCoord(i));
        }
        renderer->DeleteObjects(VAO, VBO, EBO);
        renderer->createVecBufferWithUV(vertexPositions, indices, vertexSize, indexSize, atribPosSize, VAO, VBO, EBO,
                                  atribColorSize, atribUVSize);
    }
}

void Sprite::ChangeUVCoord(int strife, glm::vec2 UVS)
{
    vertexPositions[strife] = UVS.x;
    vertexPositions[strife + 1] = UVS.y;
}
