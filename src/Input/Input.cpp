#include "Input.h"
#include <iostream>


Input::Input(GLFWwindow* engineWindow)
{
    this->engineWindow = engineWindow;
    std::cout << "Input Created" << std::endl;
}

Input::Input()
{
    std::cout << "Input Created whit no window" << std::endl;
}

Input::~Input()
{
    std::cout << "Input Destroyed" << std::endl;
}
void Input::setInputWindow(GLFWwindow* engineWindow){ this->engineWindow = engineWindow; }

bool Input::isKeyPressed(KeyKode keycode) { return glfwGetKey(engineWindow,keycode) == PRESED; }
bool Input::isKeyRepeated(KeyKode keycode) { return glfwGetKey(engineWindow,keycode) == REPEATED; }
bool Input::isKeyReleased(KeyKode keycode) { return glfwGetKey(engineWindow,keycode) == RELEASED; }
