#pragma once
#include <GLFW/glfw3.h>
class Game
{
public:
	GLFWwindow* window;
	Game();
	~Game();
		void gameLoop();
	private:
		void initGame();
		void endGame();
};

