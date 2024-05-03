#include "Game.h"

#include "Mesh/Model.h"
#include "Input/Input.h"
#include "Shape/Cube.h"
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
    const char* playerPath = "../res/images/Sonic_Mania_Sprite_Sheet.png";
    player1 = new Sprite(getRenderer(), {1, 1, 1, 1}, {0, 0, -100.0f}, {100, 100, 0},
                         playerPath,GL_NEAREST);

    obj1 = new Sprite(getRenderer(), {1, 0, 0, 1}, {150, -100, -400.0f}, {5000, 5000, 0},
                      "../res/images/parcialBackground.jpg",GL_NEAREST);
    obj1->SetRotationX(90);
    Animation animationPlayerRight = Animation(19, 205, 3, 0.5f, 830, 465, 40, 33);
    Animation animationPlayerIdle = Animation(390, 98, 3, 1.2f, 830, 465, 33, 40);
    Animation animationCartel = Animation(132, 94, 5, 0.5f, 830, 465, 49, 48);
    cartel = new Sprite(getRenderer(), {1, 1, 1, 1}, {150, 0, -400.0f}, {100, 100, 0},
                        playerPath,GL_NEAREST);
    obj2 = new Cube(getRenderer(), {30, 1, 30}, {50, 50, 50}, "../res/models/Persona.png");
    // obj2->setMaterial(BRONZE);
    Animator.insert_or_assign("Right", animationPlayerRight);
    Animator.insert_or_assign("Idle", animationPlayerIdle);
    Animator.insert_or_assign("cartel", animationCartel);
    cartel->ChangeAnimation(Animator["cartel"]);
    player1->ChangeAnimation(Animator["Idle"]);


    string resModelParcialbackgroundJpg = "../res/models/EspadaMaestra_EscudoHyliano_ModelCombinedMeshFinal.fbx";
    basicModel = new Model(resModelParcialbackgroundJpg.c_str(), getRenderer(), {0, 0, -100.0f}, {10, 10, 10});
    basicModel->SetRotationX(90);
    basicModel->SetRotationY(90);
}


//Todo: Hacer codigo más lindo

void Game::update()
{
    Vec3 newPos = {player1->GetPosition().x, player1->GetPosition().y, player1->GetPosition().z};
    Vec3 scale = {player1->GetScale().x, player1->GetScale().y, player1->GetScale().z};


    bool hasBeenPressed = false;

    float MovementSpeed = 100.5f;

#pragma region Movement with WASD
    // if ((input->isKeyPressed(KeyKode::KEY_W)))
    // {
    //     newPos.z -= MovementSpeed * getDeltaTime();
    //     hasBeenPressed = true;
    //     player1->ChangeAnimation(Animator["Idle"]);
    // }
    // if ((input->isKeyPressed(KeyKode::KEY_S)))
    // {
    //     newPos.z += MovementSpeed * getDeltaTime();
    //     hasBeenPressed = true;
    // }
    // if ((input->isKeyPressed(KeyKode::KEY_A)))
    // {
    //     newPos.x -= MovementSpeed * getDeltaTime();
    //
    //     hasBeenPressed = true;
    // }
    // if ((input->isKeyPressed(KeyKode::KEY_D)))
    // {
    //     newPos.x += MovementSpeed * getDeltaTime();
    //     hasBeenPressed = true;
    // }
#pragma endregion
#pragma region Movement with Arrows
    if (input->isKeyPressed(KeyKode::KEY_LEFT))
    {
        newPos.x -= 1.0f * 2.0f;
        player1->SetPosition(newPos);

        player1->ChangeAnimation(Animator["Right"]);
        std::cout << player1->GetScale().z << endl;
        if (player1->GetScale().x > 0)
        {
            player1->SetScale({player1->GetScale().x * -1, player1->GetScale().y, player1->GetScale().z});
        }
        hasBeenPressed = true;
    }
    if (input->isKeyPressed(KeyKode::KEY_UP))
    {
        newPos.z -= 1.0f * 2.0f;
        player1->SetPosition(newPos);
        player1->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;
    }
    if (input->isKeyPressed(KeyKode::KEY_DOWN))
    {
        newPos.z += 1.0f * 2.0f;
        player1->SetPosition(newPos);
        player1->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;
    }
    if (input->isKeyPressed(KeyKode::KEY_RIGHT))
    {
        newPos.x += 1.0f * 2;
        player1->SetPosition(newPos);
        player1->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;

        if (player1->GetScale().x < 0)
        {
            player1->SetScale({player1->GetScale().x * -1, player1->GetScale().y, player1->GetScale().z});
        }
    }
    if (input->isKeyPressed(KeyKode::KEY_E))
    {
        player1->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;
        player1->SetRotationY(1.0f);
  
    }
    if (input->isKeyPressed(KeyKode::KEY_Q))
    {
        player1->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;

        player1->SetRotationY(-1.0f);
    
    }
#pragma endregion
    camera->changeCameraObjetive(glm::vec3(newPos.x, newPos.y, newPos.z),
                                 glm::vec3(player1->GetRotation().x, player1->GetRotation().y,
                                           player1->GetRotation().z));

#pragma region Movement3DObject
    if (input->isKeyPressed(KEY_NUMPAD_1))
    {
        basicModel->SetRotationZ(1.0f);
    }  if (input->isKeyPressed(KEY_NUMPAD_3))
    {
        basicModel->SetRotationZ(-1.0f);
    } if (input->isKeyPressed(KEY_NUMPAD_7))
    {
        basicModel->SetRotationX(1.0f);
    }  if (input->isKeyPressed(KEY_NUMPAD_9))
    {
        basicModel->SetRotationX(-1.0f);
    }
    if (input->isKeyPressed(KEY_NUMPAD_4))
    {
        basicModel->SetRotationY(1.0f);
    }  if (input->isKeyPressed(KEY_NUMPAD_6))
    {
        basicModel->SetRotationY(-1.0f);
    }

#pragma  endregion
    if (!hasBeenPressed)
    {
        player1->ChangeAnimation(Animator["Idle"]);
    }
    player1->SetPosition(newPos);
    setLightPos(newPos);
    //player1->UpdateAnimation();
    //cartel->UpdateAnimation();
    //cartel->Draw();
    //player1->Draw();
    //obj1->Draw();
    //    obj2->Draw();
    basicModel->draw(getRenderer()->shaderBasicModel);
}

void Game::exit()
{
    //Animator["Right"].deleteAnimation();
    //Animator["cartel"].deleteAnimation();
    //Animator["Idle"].deleteAnimation();

    delete player1;
    delete obj1;
    // delete obj2;
    delete cartel;
    delete basicModel;
}
