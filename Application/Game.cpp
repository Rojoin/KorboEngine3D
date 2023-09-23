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
    aux = new Square(getRenderer(),{1,0,1,1},{windowWidth/2.0f,windowHeight/2.0f,0.0f},{20,100,0});
    aux2 = new Triangle(getRenderer(),{1,0,0,1,},{windowWidth/2.0f,windowHeight/2.0f,0.0f},{20,100,0});
    //aux->SetPosition({windowWidth/2.0f,windowHeight/2.0f,0.0f});
    aux2->SetPosition({windowWidth/2.0f,windowHeight/2.0f,0.0f});
    aux->SetRotationZ(10);
 
}

void Game::update() 
{
    aux->SetRotationZ(10);

    aux->Draw();
    aux2->Draw();
}

void Game::exit() 
{
    delete aux;
    delete aux2;
}