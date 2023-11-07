#pragma once
#include <glm/vec2.hpp>

class Frame
{
private :
    const static int maxFrameSize =4;
    glm::vec2 uvCoord[maxFrameSize];
public:
    glm::vec2 getUVCoord(int id);
    Frame(glm::vec2 firstUV,glm::vec2 secondUV,glm::vec2 thirdUV,glm::vec2 fourthUV);
};
