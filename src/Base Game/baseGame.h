#pragma once
#include "Renderer/renderer.h"
#include "Shape/Shape.h"
#include "Window/window.h"

class Square;

class engine
{
private:

	Renderer* renderer;
	Window* window;
	void initGame();
	void endGame();
	Shape* shape;
public:
	engine();
	~engine();
	void gameLoop();

};

