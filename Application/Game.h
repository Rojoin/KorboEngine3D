#pragma once
#include "Base Game/Engine.h"
#include "Shape/Triangle.h"
#include "Shape/Square.h"
#include "Sprite/Sprite.h"

class Game final : public Korbo::Engine
{
private:
    Sprite* aux;
    Entity2D* obj1;
    Entity2D* obj2;
    int windowWidth = 800;
    int windowHeight = 400;
public:
    Game(int windowWidth,int windowHeight);
    ~Game() override;
    void init() override;
    void update() override;
    void exit() override;
};
