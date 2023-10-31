#include "Animation.h"



Animation::Animation(int maxFrames, int frameTime, int spriteWidth, int spriteHeight, int frameWidth,
    int frameHeight)
{
    
}
Animation::Animation()
{
    maxFramesInAnimation =0;
}
bool Animation::hasFrames()
{
    return maxFramesInAnimation >0;
}
