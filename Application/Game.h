#pragma once
#include <map>

#include "Base Game/Engine.h"
#include "Entity/Entity3D.h"
#include "Shape/Triangle.h"
#include "Shape/Square.h"
#include "Sprite/Sprite.h"

class Game final : public Korbo::Engine
{
private:
    Sprite* player1;
    Sprite* cartel;
    Sprite* obj1;
    Entity3D* obj2;
    map<string, Animation> Animator;
    int windowWidth = 800;
    int windowHeight = 400;
public:
    Game(int windowWidth,int windowHeight);
    ~Game() override;
    void init() override;
    void update() override;
    void exit() override;
};
