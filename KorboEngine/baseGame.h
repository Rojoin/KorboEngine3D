#pragma once
#include "renderer.h"
#include "window.h"

class engine
{
private:

	Renderer* renderer;
	Window* window;
	void initGame();
	void endGame();
public:
	engine();
	~engine();
	void gameLoop();

};

