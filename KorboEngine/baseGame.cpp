#include "baseGame.h"

engine::engine()
{
	initGame();
}

engine::~engine()
{
	endGame();
}

void engine::initGame()
{
	/* Initialize the library */
	if (!glfwInit())
		return;

	/* Create a windowed mode window and its OpenGL context */
	window = new Window(640, 480, "Korbo Engine", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return;
	}
	renderer = new Renderer(window);


}

void engine::gameLoop()
{
	while (!glfwWindowShouldClose(window->getWindow()))
	{
		renderer->RenderScreen();
	}
}

void engine::endGame()
{
	glfwTerminate();
}
