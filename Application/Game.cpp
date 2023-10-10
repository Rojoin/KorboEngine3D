#include "Game.h"
#include "Input/Input.h"
#include "Sprite/Sprite.h"

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
    aux = new Sprite(getRenderer(),{1,1,1,1},{windowWidth/2.0f,windowHeight/2.0f,0.0f},{100,100,0},"../res/images/test.png",400,400);
    aux2 = new Triangle(getRenderer(),{1,0,0,1,},{windowWidth/2.0f,windowHeight/2.0f,0.0f},{20,100,0});
    //aux->SetPosition({windowWidth/2.0f,windowHeight/2.0f,0.0f});
    aux2->SetPosition({windowWidth/2.0f,windowHeight/2.0f,0.0f});
    aux->SetRotationZ(10);
 
}

void Game::update() 
{
    Vec3 newPos;
    
    if (input->isKeyPressed(D))
    {
        newPos.x = aux->GetPosition().x + 1.0f;
        newPos.y = aux->GetPosition().y;
        newPos.z = aux->GetPosition().z;
        aux->SetPosition( newPos);
    }

    if (input->isKeyPressed(A))
    {
        newPos.x = aux->GetPosition().x - 1.0f;
        newPos.y = aux->GetPosition().y;
        newPos.z = aux->GetPosition().z;
        aux->SetPosition( newPos);
    }

    

    aux->Draw();
    aux2->Draw();

    
}

void Game::exit() 
{
    delete aux;
    delete aux2;
}