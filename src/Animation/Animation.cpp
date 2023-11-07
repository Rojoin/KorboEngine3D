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
