#include "Engine.h"

#include "Globals/Time.h"
#include "Shape/Square.h"
#include "Shape/Triangle.h"

using namespace Korbo;
 Engine::Engine(int windowWidth,int windowHeight)
{
    initGame(windowWidth,windowHeight);
}

 Engine::~Engine()
{
    endGame();
}

Renderer* Engine::getRenderer()
{
     return renderer;
}

void Engine::init()
{
}

void Engine::update()
{
}

void Engine::exit()
{
}

void Engine::initGame(int windowWhidth,int windowHeight)
{
    /* Initialize the library */
    if (!glfwInit())
        return;

    /* Create a windowed mode window and its OpenGL context */
    window = new Window(windowWhidth, windowHeight, "Korbo Engine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }
    renderer = new Renderer(window);
    input = new Input(window->getWindow());
}

void Engine::gameLoop()
{
    while (!glfwWindowShouldClose(window->getWindow()))
    {
        Time::setTime();
        renderer->BeginDrawing();
        update();
        renderer->EndDrawing();
    }
}

void Engine::endGame()
{
    delete window;
    delete renderer;
    glfwTerminate();
}
