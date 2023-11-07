#include "Frame.h"

#include <iostream>


glm::vec2 Frame::getUVCoord(int id)
{
    if (id >= maxFrameSize && id < 0)
    {
        std::cout << "Id UV outside range" << std::endl;
        return {0, 0};
    }
    else
    {
        return uvCoord[id];
    }
}

Frame::Frame(glm::vec2 firstUV, glm::vec2 secondUV, glm::vec2 thirdUV, glm::vec2 fourthUV)
{
    uvCoord[0] = firstUV;
    uvCoord[1] = secondUV;
    uvCoord[2] = thirdUV;
    uvCoord[3] = fourthUV;
}
