#pragma once
#include "Animation/Animation.h"
#include "Shape/Shape.h"

class EXPORT Sprite  : public Entity2D
{
private:
    int width;
    int height;
    int nrChannels;
    Animation animation;
public:
    Sprite(Renderer* renderer, Vec4 color, Vec3 position, Vec3 newScale, const char* imagePath);
    Sprite(Renderer* renderer, Vec4 color, Vec3 position, Vec3 newScale, const char* imagePath, GLint textureFilter);
    int getWidth();
    int getHeight();
    void Draw() override;
    ~Sprite() override;
    void ChangeAnimation(Animation animation);
    void ChangeAnimation();
    void UpdateAnimation();
    void ChangeUVCoord(int strife, glm::vec2 UVS);
};
