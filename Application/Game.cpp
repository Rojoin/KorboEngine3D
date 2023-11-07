﻿#include "Game.h"
#include "Input/Input.h"
#include "Sprite/Sprite.h"

Game::Game(int windowWidth, int windowHeight) : Engine(windowWidth, windowHeight)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    init();
}

Game::~Game()
{
    exit();
}

void Game::init()
{
    const char* filePath = "../res/images/KirbySleepSpriteSheet.png";

    aux = new Sprite(getRenderer(), {1, 1, 1, 1}, {windowWidth / 2.0f, windowHeight / 2.0f, 0.0f}, {400, 400, 0},
                     filePath,GL_NEAREST);
    //aux = new Square(getRenderer(),{1,1,1,1},{windowWidth/2.0f,windowHeight/2.0f,0.0f},{100,100,0});
    Animation animation = Animation(4, 1.2f, 120, 22, 120 / 4, 22);
    aux->ChangeAnimation(animation);
}

void Game::update()
{
    Vec3 newPos = {0, 0, 0};

    if (input->isKeyPressed(KeyKode::KEY_A))
    {
        newPos.y = aux->GetPosition().y;
        newPos.z = aux->GetPosition().z;
        // newPos.x = aux->GetPosition().x + 1.0f;
        aux->MovePosition(newPos);
    }


    if (input->isKeyPressed(KeyKode::KEY_D))
    {
        //newPos.x = aux->GetPosition().x - 1.0f;
        newPos.y = aux->GetPosition().y;
        newPos.z = aux->GetPosition().z;
        aux->MovePosition(newPos);
        aux->SetRotationZ(-1);
    }
    if (input->isKeyPressed(KeyKode::KEY_W))
    {
        newPos.x = 2;
        newPos.y = 500;
        newPos.z = aux->GetPosition().z;
        aux->SetPosition(newPos);
    }


    aux->UpdateAnimation();
    aux->Draw();
}

void Game::exit()
{
    delete aux;
}
