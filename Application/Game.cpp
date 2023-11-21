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
    //const char* filePath = "../res/images/KirbySleepSpriteSheet.png";
    const char* filePath = "../res/images/linkSprite.png";

    aux = new Sprite(getRenderer(), {1, 1, 1, 1}, {windowWidth / 2.0f, windowHeight / 2.0f, 0.0f}, {100, 100, 0},
                     filePath,GL_NEAREST);
    obj1 = new Square(getRenderer(), {1, 1, 1, 1}, {windowWidth / 4.0f, windowHeight / 2.0f, 0.0f}, {100, 100, 0});
    obj2 = new Square(getRenderer(), {1, 1, 0, 1}, {windowWidth / 2.0f, windowHeight / 2.0f, 0.0f}, {100, 100, 0});
    Animation animationPlayerUp = Animation(0, 832 / 8, 10, 1.2f, 960, 832, 960 / 10, 832 / 8);
    Animation animationPlayerDown = Animation(0, (832 / 8) *3, 10, 1.2f, 960, 832, 960 / 10, 832 / 8);
    Animation animationPlayerLeft = Animation(0, (832 / 8) *2, 10, 1.2f, 960, 832, 960 / 10, 832 / 8);
    Animation animationPlayerRight = Animation(0, 0, 10, 1.2f, 960, 832, 960 / 10, 832 / 8);
    Animation animationPlayerIdle = Animation(0, 728 , 3, 1.2f, 960, 832, 960 / 10, 93);
    Animator.insert_or_assign("Up", animationPlayerUp);
    Animator.insert_or_assign("Down", animationPlayerDown);
    Animator.insert_or_assign("Left", animationPlayerLeft);
    Animator.insert_or_assign("Right", animationPlayerRight);
    Animator.insert_or_assign("Idle", animationPlayerIdle);
}

void Game::update()
{
    Vec3 newPos = {aux->GetPosition().x, aux->GetPosition().y, aux->GetPosition().z};
    Vec3 newPos2 = {0, 0, 0};

    bool hasBeenPressed = false;
    if (input->isKeyPressed(KeyKode::KEY_A))
    {
        newPos.x -= 1.0f;
        aux->SetPosition(newPos);

        aux->ChangeAnimation(Animator["Left"]);
        hasBeenPressed = true;
    }
     if (input->isKeyPressed(KeyKode::KEY_W))
    {
        newPos.y += 1.0f;
        aux->SetPosition(newPos);
        aux->ChangeAnimation(Animator["Up"]);
        hasBeenPressed = true;
    }
     if (input->isKeyPressed(KeyKode::KEY_S))
    {
        newPos.y -= 1.0f;
        aux->SetPosition(newPos);
        aux->ChangeAnimation(Animator["Down"]);
        hasBeenPressed = true;
    }
    if (input->isKeyPressed(KeyKode::KEY_D))
    {
        newPos.x += 1.0f;
        aux->SetPosition(newPos);
        aux->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;
    }

    if (!hasBeenPressed)
    {
        aux->ChangeAnimation(Animator["Idle"]);
    }

    if (input->isKeyPressed(KeyKode::KEY_RIGHT))
    {
        newPos2.x = aux->GetPosition().x + 1.0f;
        aux->SetPosition(newPos2);
    }

    if (input->isKeyPressed(KeyKode::KEY_LEFT))
    {
        newPos2.x = aux->GetPosition().x - 1.0f;
        aux->SetPosition(newPos2);
    }

    if (Colitions::CheckCollitions(obj1, aux))
    {
        cout << "Collision" << endl;
    }

    aux->UpdateAnimation();
    aux->Draw();
    obj1->Draw();
    obj2->Draw();
}

void Game::exit()
{
    delete aux;
    delete obj1;
    delete obj2;
}
