#include "Game.h"

#include "Globals/Time.h"
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
    const char* playerPath = "../res/images/Sonic_Mania_Sprite_Sheet.png";
    //  const char* filePath = "../res/images/linkSprite.png";
    const char* backgroundPath = "../res/images/parcialBackground.jpg";
    player1 = new Sprite(getRenderer(), {1, 1, 1, 1}, {0, 0, 0.0f}, {100, 100, 0},
                         playerPath,GL_NEAREST);
    cartel = new Sprite(getRenderer(), {1, 1, 1, 1}, {windowWidth / 2.0f, windowHeight / 2.0f, 0.0f}, {100, 100, 0},
                        playerPath,GL_NEAREST);
    fondo = new Sprite(getRenderer(), {1, 1, 1, 1}, {windowWidth / 2.0f, windowHeight / 2.0f, 0.0f}, {700, 500, 0},
                       backgroundPath,GL_NEAREST);
    
    Animation animationPlayerRight = Animation(19, 205, 3, 0.5f, 830, 465, 40, 33);
    Animation animationPlayerIdle = Animation(390, 98, 3, 1.2f, 830, 465, 33, 40);
    Animation animationCartel = Animation(132, 94, 5, 0.5f, 830, 465, 49, 48);

    Animator.insert_or_assign("Right", animationPlayerRight);
    Animator.insert_or_assign("Idle", animationPlayerIdle);
    Animator.insert_or_assign("cartel", animationCartel);
    cartel->ChangeAnimation(Animator["cartel"]);
// animationCartel.deleteAnimation();
// animationPlayerRight.deleteAnimation();
// animationCartel.deleteAnimation();
    //delete playerPath;
    //delete backgroundPath;
}

void Game::update()
{
    Vec3 newPos = {player1->GetPosition().x, player1->GetPosition().y, player1->GetPosition().z};
    Vec3 scale = {player1->GetScale().x, player1->GetScale().y, player1->GetScale().z};
 

    bool hasBeenPressed = false;
    if (input->isKeyPressed(KeyKode::KEY_A))
    {
        newPos.x -= 1.0f * 2.0f;
        player1->SetPosition(newPos);

        player1->ChangeAnimation(Animator["Right"]);
        std::cout << player1->GetScale().z << endl;
        if (player1->GetScale().x > 0)
        {
            player1->SetScale({player1->GetScale().x*-1, player1->GetScale().y, player1->GetScale().z });
        }
        hasBeenPressed = true;
        if (Colitions::CheckCollitions(cartel, player1))
        {
            cout << "Collision" << endl;
        }
    }
    if (input->isKeyPressed(KeyKode::KEY_W))
    {
        newPos.y += 1.0f* 2.0f;
        player1->SetPosition(newPos);
        player1->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;
        if (Colitions::CheckCollitions(cartel, player1))
        {
            cout << "Collision" << endl;
        }
    }
    if (input->isKeyPressed(KeyKode::KEY_S))
    {
        newPos.y -= 1.0f*  2.0f;
        player1->SetPosition(newPos);
        player1->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;
        if (Colitions::CheckCollitions(cartel, player1))
        {
            cout << "Collision" << endl;
        }
    }
    if (input->isKeyPressed(KeyKode::KEY_D))
    {
        newPos.x += 1.0f * 2;
        player1->SetPosition(newPos);
        player1->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;
        
        if (player1->GetScale().x < 0)
        {
            player1->SetScale({player1->GetScale().x *-1, player1->GetScale().y, player1->GetScale().z});
        }
        if (Colitions::CheckCollitions(cartel, player1))
        {
            cout << "Collision" << endl;
        }
    }

    if (!hasBeenPressed)
    {
        //player1->ChangeAnimation(Animator["Idle"]);
    }


    
    if (Colitions::CheckCollitions(player1, cartel))
    {
        cout << "Collision" << endl;
    }

    fondo->Draw();
    player1->UpdateAnimation();
    player1->Draw();
    cartel->UpdateAnimation();
    cartel->Draw();
}

void Game::exit()
{
    //Animator["Right"].deleteAnimation();
    //Animator["cartel"].deleteAnimation();
    //Animator["Idle"].deleteAnimation();
    
    delete player1;
    delete obj1;
    delete obj2;
    delete fondo;
    delete cartel;
    
}
