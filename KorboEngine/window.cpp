#include "window.h"

Window::Window(int width,int height, const char* title, GLFWmonitor* monitor,GLFWwindow* share)
{
	this->width = width;
	this->height = height;
	this->title = title;
	this->monitor = monitor;
	this->share = share;
	initWindow();
}
Window::Window(int width,int height, const char* title)
{
	this->width = width;
	this->height = height;
	this->title = title;
	this->monitor = NULL;
	this->share = NULL;
	initWindow();
}
Window::Window(int width,int height)
{
	this->width = width;
	this->height = height;
	this->title = "Hello World!";
	this->monitor = NULL;
	this->share = NULL;
	initWindow();
}

Window::~Window()
{
	destroyWindow();
}

void Window::initWindow()
{
	this->GlfWindow = glfwCreateWindow(width, height, title, monitor, share);

	/* Make the window's context current */
	glfwMakeContextCurrent(GlfWindow);
}

void Window::destroyWindow()
{
	
}

GLFWwindow* Window::getWindow()
{
	return GlfWindow;
}
