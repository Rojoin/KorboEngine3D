// Application.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#pragma once

#include "Base Game/baseGame.h"

int main()
{
	Korbo::engine* game = new Korbo::engine;
	game->gameLoop();
	delete game;
}

