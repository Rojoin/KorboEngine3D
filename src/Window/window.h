#pragma once
#include <GLFW/glfw3.h>
#include "Globals/dllHeader.h"

class EXPORT Window
{
private:
	GLFWwindow* GlfWindow;
	int width;
	int height;
	const char* title;
	GLFWmonitor* monitor;
	GLFWwindow* share;
	void initWindow();
	void destroyWindow();
public:

	Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	Window(int width, int height, const char* title);
	Window(int width, int height);
	~Window();
	GLFWwindow* getWindow();
};

