#include "Frame.h"

#include <iostream>


 glm::vec2 Frame::getUVCoord(int id)
 {
     if (id >= maxFrameSize && id<0)
     {
         std::cout <<"Id UV outside range" << std::endl;
         return {0,0};
     }
     else
     {
         return uvCoord[id];
     }
 }
