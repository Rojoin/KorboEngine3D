#pragma once

#include "Base Game/baseGame.h"
#include "Shape/Triangle.h"
#include "Shape/Square.h"

class Game final : public Korbo::Engine
{
private:
    Shape* aux;
    int windowWidth = 800;
    int windowHeight = 400;
public:
    Game(int windowWidth,int windowHeight);
    ~Game() override;
    void init() override;
    void update() override;
    void exit() override;
};
