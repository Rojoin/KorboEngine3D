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
    const char* filePath = "../res/images/test.png";
    aux2 = new Triangle(getRenderer(),{windowWidth/2.0f,windowHeight/2.0f,0.0f},{100,100,0});
    aux3 = new Triangle(getRenderer(),{aux2->GetPosition().x,aux2->GetPosition().y,aux2->GetPosition().z},{50,50,0});
    aux = new Sprite(getRenderer(),{1,1,1,1},{windowWidth/2.0f,windowHeight/2.0f,0.0f},{600,600,0},filePath,1024,1024);
    //aux = new Square(getRenderer(),{1,1,1,1},{windowWidth/2.0f,windowHeight/2.0f,0.0f},{100,100,0});
    
 
}

void Game::update() 
{
    Vec3 newPos = {0,0,0};
    
    if (input->isKeyPressed(KeyKode::KEY_A))
    {
        newPos.y = aux->GetPosition().y;
        newPos.z = aux->GetPosition().z;
       // newPos.x = aux->GetPosition().x + 1.0f;
        aux->MovePosition( newPos);
    }

        aux->SetRotationZ(0.5);
    if (input->isKeyPressed(KeyKode::KEY_D))
    {
        //newPos.x = aux->GetPosition().x - 1.0f;
        newPos.y = aux->GetPosition().y;
        newPos.z = aux->GetPosition().z;
        aux->MovePosition( newPos);
        aux->SetRotationZ(-1);
    }
    if (input->isKeyPressed(KeyKode::KEY_W))
    {
        newPos.x = 2;
        newPos.y = 500;
        newPos.z = aux->GetPosition().z;
        aux->SetPosition( newPos);
    }


    

    aux2->Draw();
    aux3->Draw();


    
}

void Game::exit() 
{
    delete aux;
  
}