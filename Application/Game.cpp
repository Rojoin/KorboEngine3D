#include "Game.h"
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
    obj1 = new Square(getRenderer(),{1,1,1,1},{windowWidth/4.0f,windowHeight/2.0f,0.0f},{100,100,0});
    obj2 = new Square(getRenderer(),{1,1,0,1},{windowWidth/2.0f,windowHeight/2.0f,0.0f},{100,100,0});
    Animation animation = Animation(4, 1.2f, 120, 22, 120 / 4, 22);
    aux->ChangeAnimation(animation);
}

void Game::update()
{
    Vec3 newPos = {obj1->GetPosition().x, obj1->GetPosition().y, obj1->GetPosition().z};
    Vec3 newPos2 = {0, 0, 0};

    if (input->isKeyPressed(KeyKode::KEY_A))
    {
        newPos .x -=1.0f;
        obj1->SetPosition(newPos);
    }
    if (input->isKeyPressed(KeyKode::KEY_W))
    {
        newPos .y +=1.0f;
        obj1->SetPosition(newPos);
    }if (input->isKeyPressed(KeyKode::KEY_S))
    {
        newPos .y -= 1.0f;
        obj1->SetPosition(newPos);
    }


    if (input->isKeyPressed(KeyKode::KEY_D))
    {
       newPos.x += 1.0f;
        obj1->SetPosition(newPos);
    }
    
    if (input->isKeyPressed(KeyKode::KEY_RIGHT))
    {
        newPos2.x = obj2->GetPosition().x + 1.0f;
        obj2->SetPosition(newPos2);
    }

    if (input->isKeyPressed(KeyKode::KEY_LEFT))
    {
        newPos2.x = obj2->GetPosition().x - 1.0f;
        obj2->SetPosition(newPos2);
    }

    if (Colitions::CheckCollitions(obj1,obj2))
    {
        cout << "Collision" << endl;
    }
    
     //aux->UpdateAnimation();
    // aux->Draw();
    obj1->Draw();
    obj2->Draw();
}

void Game::exit()
{
    delete aux;
    delete obj1;
    delete obj2;
}
