// Application.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#pragma once

#include "Base Game/baseGame.h"
#include "Shape/Triangle.h"
#include "Shape/Square.h"
class Game;
Game* game;
Shape* aux;
 class Game final : public Korbo::engine
{

public:
	Game()
	{
		init();
	}
	~Game() override;
	void init() override;
	void update() override;
	void exit() override;
};

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
int main()
{
	game = new Game();
	game->gameLoop();
	delete game;
}

