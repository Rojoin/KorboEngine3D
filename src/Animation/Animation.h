#pragma once
#include <list>
#include <vector>

#include "Frame.h"
#include "Globals/dllHeader.h"


class EXPORT Animation
{
public:
    Animation(int maxFrames, int frameTime, int spriteWidth, int spriteHeight, int frameWidth, int frameHeight);
    Animation();
    bool hasFrames();
    void addFrames();
    void update();
    Frame* currentFrame;
    std::list<Frame*> totalFrames;
    
private:
    std::vector<Frame> framesInAnimation;
    int spriteWidth;
    int spriteHeight;
    int frameWidth;
    int frameHeight;
    int currentFrameCounter;
    int maxFramesInAnimation;
    int frameTime;
    int frameLengh;
};
