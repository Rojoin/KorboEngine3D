#pragma once
#include "Base Game/Engine.h"
#include "Shape/Triangle.h"
#include "Shape/Square.h"

class Game final : public Korbo::Engine
{
private:
    Entity2D* aux;
    Entity2D* aux2;
    Entity2D* aux3;
    int windowWidth = 800;
    int windowHeight = 400;
public:
    Game(int windowWidth,int windowHeight);
    ~Game() override;
    void init() override;
    void update() override;
    void exit() override;
};
