#include "Animation.h"


Animation::Animation(int maxFrames, int frameTime, int spriteWidth, int spriteHeight, int frameWidth,
                     int frameHeight)
{
    this->maxFramesInAnimation = maxFrames;
    this->frameTime = frameTime;
    this->spriteHeight = spriteHeight;
    this->spriteWidth = spriteWidth;
    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;
    addFrames();
    currentFrame = totalFrames.front();
}

Animation::Animation()
{
    while (!totalFrames.empty())
    {
        Frame* aux = totalFrames.back();
        totalFrames.pop_back();
        delete aux;
    }
    maxFramesInAnimation = 0;
}

bool Animation::hasFrames()
{
    return maxFramesInAnimation > 0;
}

void Animation::addFrames()
{
    float spriteWidthF = spriteWidth;
    float spriteHeightF = spriteHeight;
    for (int i = 0; i < maxFramesInAnimation; ++i)
    {
        glm::vec2 topRight = glm::vec2(((i * frameWidth) + frameWidth) / spriteWidthF,
                                       (frameHeight / spriteHeightF));
        glm::vec2 botRight = glm::vec2(((i * frameWidth) + frameWidth) / spriteWidthF,
                                       0);
        glm::vec2 botLeft = glm::vec2((i * frameWidth) / spriteWidthF,
                                      0);
        glm::vec2 topLeft = glm::vec2((i * frameWidth) / spriteWidthF,
                                      (frameHeight / spriteHeightF));

        Frame* aux = new Frame(topRight, botRight, botLeft, topLeft);
        totalFrames.push_front(aux);
    }
}

void Animation::update()
{
    currentFrame = totalFrames.front();
}
