#include "Game.h"

Game::Game(int windowWidth,int windowHeight) : engine(windowWidth,windowHeight)
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
    aux = new Square(getRenderer(),{1,0,1,1});
}

void Game::update() 
{
    aux->Draw();
}

void Game::exit() 
{
    delete aux;
}