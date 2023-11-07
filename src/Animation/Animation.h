#pragma once

#include <vector>

#include "Frame.h"
#include "Globals/dllHeader.h"


class EXPORT Animation
{
public:
    Animation(int maxFrames, float frameTime, int spriteWidth, int spriteHeight, int frameWidth, int frameHeight);
    Animation();
    bool hasFrames();
    void addFrames();
    void update();
    Frame* currentFrame;
    std::vector<Frame*> totalFrames;
    
private:
    std::vector<Frame> framesInAnimation;
    int spriteWidth;
    int spriteHeight;
    int frameWidth;
    int frameHeight;
    int currentFrameCounter;
    int maxFramesInAnimation;
    float frameTime;
    float currentTime;
};
