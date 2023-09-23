#include <GL/glew.h>
#include "window.h"

#include <cstdio>
#include <GLFW/glfw3.h>

Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
    this->width = width;
    this->height = height;
    this->title = title;
    this->monitor = monitor;
    this->share = share;
    initWindow();
}

Window::Window(int width, int height, const char* title)
{
    this->width = width;
    this->height = height;
    this->title = title;
    this->monitor = NULL;
    this->share = NULL;
    initWindow();
}

Window::Window(int width, int height)
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

int Window::GetWindowWidth() { return width; }

int Window::GetWindowHeight() { return height; }


void Window::initWindow()
{
    this->GlfWindow = glfwCreateWindow(width, height, title, monitor, share);

    /* Make the window's context current */
    glfwMakeContextCurrent(GlfWindow);
    if (glewInit() != GLEW_OK)
    {
        printf("glew not initialized\n");
    }
}

void Window::destroyWindow()
{
}

GLFWwindow* Window::getWindow()
{
    return GlfWindow;
}

float Window::getHeight() { return (float)height; }

float Window::getWidth() { return (float)width; }
