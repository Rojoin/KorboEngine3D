#include "Input.h"
#include <iostream>

//Input* Input::_instance = nullptr;

Input::Input(GLFWwindow* engineWindow)
{
    //if (_instance != nullptr && _instance != this)
    //{
    //    delete this;
    //    return;
    //}
    //
    //_instance = this;
    
    this->engineWindow = engineWindow;
    std::cout << "Input Created" << std::endl;
}

Input::Input()
{
   // if (_instance != nullptr && _instance != this)
   // {
   //     delete this;
   //     return;
   // }
   // _instance = this;

    std::cout << "Input Created whit no window" << std::endl;
}

Input::~Input()
{
    std::cout << "Input Destroyed" << std::endl;
}

//Input* Input::getInstance()
//{
//    if (!_instance)
//        _instance = new Input();
//    
//    return _instance;
//}
void Input::setInputWindow(GLFWwindow* engineWindow){ this->engineWindow = engineWindow; }

bool Input::isKeyPressed(KeyKode keycode) { return glfwGetKey(engineWindow,keycode) == PRESED; }
bool Input::isKeyRepeated(KeyKode keycode) { return glfwGetKey(engineWindow,keycode) == REPEATED; }
bool Input::isKeyReleased(KeyKode keycode) { return glfwGetKey(engineWindow,keycode) == RELEASED; }
