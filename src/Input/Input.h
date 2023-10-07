#pragma once
#include "KeyCode.h"
#include "Globals/dllHeader.h"

class EXPORT Input
{
public:
    Input(GLFWwindow* engineWindow);
    Input();
    ~Input();
    void setInputWindow(GLFWwindow* engineWindow);
    //static Input* getInstance();
    
    bool isKeyPressed(KeyKode keycode);
    bool isKeyRepeated(KeyKode keycode);
    bool isKeyReleased(KeyKode keycode);
    
private:
   //static Input * _instance;
    GLFWwindow* engineWindow;
};
