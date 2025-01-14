﻿#pragma once
#include <map>

#include "Base Game/Engine.h"
#include "Mesh/Model.h"
#include "Planes/Plane.h"
#include "Shape/Triangle.h"
#include "Shape/Square.h"
#include "Sprite/Sprite.h"

class Game final : public Korbo::Engine
{
private:
    Sprite* player1;
    Sprite* cartel;
    Sprite* obj1;
    Sprite* obj2;
    Sprite* obj3;
    Model* obj4;
    Model* dummy;
    Model* house;
    Model* backPack;

    map<string, Animation> Animator;
    int windowWidth = 1600;
    int windowHeight = 900;
public:
    Game(int windowWidth,int windowHeight);
    ~Game() override;
    void init() override;
    void update() override;
    void exit() override;
};
