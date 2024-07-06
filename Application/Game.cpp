﻿#include "Game.h"

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
    player1 = new Sprite(getRenderer(), {1, 1, 1, 1}, {0, 0, -100.0f}, {100, 100, 100},
                         playerPath,GL_NEAREST);

    obj1 = new Sprite(getRenderer(), {1, 0, 0, 1}, {150, -100, -400.0f}, {5000, 5000, 0},
                      "../res/images/parcialBackground.jpg",GL_NEAREST);
    obj1->tranform->setRotationX(90);
    Animation animationPlayerRight = Animation(19, 205, 3, 0.5f, 830, 465, 40, 33);
    Animation animationPlayerIdle = Animation(390, 98, 3, 1.2f, 830, 465, 33, 40);
    Animation animationCartel = Animation(132, 94, 5, 0.5f, 830, 465, 49, 48);
    cartel = new Sprite(getRenderer(), {1, 1, 1, 1}, {150, 0, -400.0f}, {100, 100, 0},
                        playerPath,GL_NEAREST);
    obj2 = new Cube(getRenderer(), {30, 1, 30}, {50, 50, 50}, "../res/images/Persona.png");
    obj2->setMaterial(DEFAULT_MATERIAL);
    Animator.insert_or_assign("Right", animationPlayerRight);
    Animator.insert_or_assign("Idle", animationPlayerIdle);
    Animator.insert_or_assign("cartel", animationCartel);
    cartel->ChangeAnimation(Animator["cartel"]);
    player1->ChangeAnimation(Animator["Idle"]);


    string resModelParcialbackgroundJpg = "../res/models/CH_Dummy_HurtV2.fbx";
    dummy = new Model(resModelParcialbackgroundJpg.c_str(), getRenderer(), {400, 0, -100.0f}, {90, 0, 0},{1, 1, 1},false,root);
    resModelParcialbackgroundJpg = "../res/models/SM_Doors_V2.fbx";
    house = new Model(resModelParcialbackgroundJpg.c_str(), getRenderer(), {-400, -100, -400.0f}, {0, 0, 0},{50, 50, 50},false,root);
    resModelParcialbackgroundJpg = "../res/models/TanqueDePrueba.fbx";
    backPack = new Model(resModelParcialbackgroundJpg.c_str(), getRenderer(), {100, 0, -100.0f}, {90, 90, 90},{10, 10, 10}, true,root);
    house->setNewTextures("../res/models","T_Doors_BC.png",false,"texture_baseColor");
  
}


void Game::update()
{
    Vec3 newPos = {player1->GetPosition().x, player1->GetPosition().y, player1->GetPosition().z};

    bool hasBeenPressed = false;
    // system("cls");
    float MovementSpeed = 100.5f;
    //   cout << "Global Sonic pos:" << player1->tranform->getGlobalPosition().toString() << endl;
    //   cout << "Local Sonic pos:" << player1->tranform->getLocalPosition().toString() << endl;
    //   cout << "Local Sonic Scale:" << player1->tranform->getScale().toString() << endl;
    //   cout << "Global Sonic Scale:" << player1->tranform->getGlobalScaleVec3().toString() << endl;
    //   cout << "Sonic Rotation:" << player1->tranform->getRotation().toString() << endl;
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
        house->tranform->childs[0]->setPosition(newPos);

        player1->ChangeAnimation(Animator["Right"]);


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
        house->tranform->childs[0]->setPosition(newPos);
        player1->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;
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
        dummy->SetRotationZ(1.0f);
    }
    if (input->isKeyPressed(KEY_NUMPAD_3))
    {
        dummy->SetRotationZ(-1.0f);
    }
    if (input->isKeyPressed(KEY_NUMPAD_7))
    {
        dummy->SetRotationX(1.0f);
    }
    if (input->isKeyPressed(KEY_NUMPAD_9))
    {
        dummy->SetRotationX(-1.0f);
    }
    if (input->isKeyPressed(KEY_NUMPAD_4))
    {
        dummy->SetRotationY(1.0f);
    }
    if (input->isKeyPressed(KEY_NUMPAD_6))
    {
        dummy->SetRotationY(-1.0f);
    }

#pragma  endregion

#pragma region Draw
    if (!hasBeenPressed)
    {
        player1->ChangeAnimation(Animator["Idle"]);
    }
    player1->SetPosition(newPos);
    setLightPos(newPos);
    player1->UpdateAnimation();
    cartel->UpdateAnimation();
    cartel->Draw();
    player1->Draw();
    obj1->Draw();
    obj2->Draw();
  //  dummy->Draw();
    house->Draw();
    //backPack->Draw();

#pragma endregion
}

void Game::exit()
{
    delete player1;
    delete obj1;
    delete obj2;
    delete cartel;
    //delete house;
    // if (backPack != nullptr)
    // {
    //     delete backPack;
    //     backPack = nullptr;
    // }
    // if (dummy != nullptr)
    // {
    //     delete dummy;
    //     dummy = nullptr;
    // }
}
