#include "Time.h"

#include <GLFW/glfw3.h>
double Time::oldTime = glfwGetTime();
float Time::getDeltaTime()
{
    double timeSinceStart = glfwGetTime();
    float deltaTime;
    deltaTime = timeSinceStart - oldTime;
    oldTime = timeSinceStart;
    return deltaTime;
}

float Time::getTime()
{
    return glfwGetTime();
}
