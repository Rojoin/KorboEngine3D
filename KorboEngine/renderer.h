#pragma once
#include "GLFW/glfw3.h"
#include <iostream>
#include "window.h"

using namespace std;

class Renderer
{
public:
	Renderer(Window* window);
	Renderer(Window* window, GLbitfield mask);
	~Renderer();
	void RenderScreen();
	void SetWindow(Window* window);
	void Setbitfield(GLbitfield mask);
	GLbitfield Getbitfield();
private:
	Window* GLFWW;
	GLbitfield mask;
};