#pragma once
#include <vector>

#include "Frame.h"
#include "Sprite/Sprite.h"


class final Animation
{
public:
    Animation(int maxFrames, int frameTime, int spriteWidth, int spriteHeight, int frameWidth, int frameHeight);
    Animation();
    bool hasFrames();
    Frame currentFrame;
    
private:
    vector<Frame> framesInAnimation;
    int spriteWidth;
    int spriteHeight;
    int frameWidth;
    int frameHeight;
    int currentFrameCounter;
    int maxFramesInAnimation;
    int frameTime;
    int frameLengh;
};
