#pragma once
#include "Shape/Shape.h"

class EXPORT Sprite final : public Entity2D
{
private:
    int width;
    int height;
    int nrChannels;
public:
    Sprite(Renderer* renderer, Vec4 color, Vec3 position, Vec3 newScale, const char* imagePath);
    int getWidth();
    int getHeight();
    void Draw() override;
    ~Sprite() override;
};
