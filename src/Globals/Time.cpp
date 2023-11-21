#include "Time.h"

#include <GLFW/glfw3.h>
double Time::oldTime = glfwGetTime();
float Time::currentTime = glfwGetTime();
float Time::getDeltaTime()
{
    return currentTime;
}
void Time::setTime()
{
    double timeSinceStart = glfwGetTime();
    float deltaTime;
    deltaTime = timeSinceStart - oldTime;
    oldTime = timeSinceStart;
    currentTime= deltaTime;
}
float Time::getTime()
{
    return glfwGetTime();
}
