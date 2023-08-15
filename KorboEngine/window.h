#pragma once
#include <GLFW/glfw3.h>

class Window
{
private:
	GLFWwindow* GlfWindow;
	int width;
	int height;
	const char* title;
	GLFWmonitor* monitor;
	GLFWwindow* share;
	
	Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	Window(int width, int height, const char* title);
	Window(int width, int height);
	~Window();
public:
	void initWindow();
	void destroyWindow();
	GLFWwindow* getWindow();
};

