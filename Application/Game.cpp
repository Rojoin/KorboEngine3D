#include "Game.h"

Game::Game(int windowWidth,int windowHeight) : Engine(windowWidth,windowHeight)
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
    knuckles = new Triangle(getRenderer(),{1,0,0,1},{50,50,0.0f},{100,100,0});
    Amy = new Triangle(getRenderer(),{1,0,0.5f,1},{(float)windowWidth-50,(float)windowHeight/2,0.0f},{100,100,0});
}

void Game::update() 
{
    
    knuckles->SetRotationZ(10);
    knuckles->SetPosition({ knuckles->GetPosition().x + 1,knuckles->GetPosition().y + 1 ,0 });
    knuckles->Draw();
    Amy->Draw();
}

void Game::exit() 
{
    delete knuckles;
    delete Amy;
}