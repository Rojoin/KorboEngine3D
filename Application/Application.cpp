// Application.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include "Game.h"

int main()
{
	Game *game;
	game = new Game(1600,900);
	game->gameLoop();
	delete game;
}

