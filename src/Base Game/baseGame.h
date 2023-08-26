#pragma once
#include "Renderer/renderer.h"
#include "Window/window.h"

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

