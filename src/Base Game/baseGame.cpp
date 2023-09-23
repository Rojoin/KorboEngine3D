#include "baseGame.h"

#include "Shape/Square.h"
#include "Shape/Triangle.h"

using namespace Korbo;
 engine::engine()
{
    initGame();
}

 engine::~engine()
{
    endGame();
}

Renderer* engine::getRenderer()
{
     return renderer;
}

void engine::init()
{
}

void engine::update()
{
}

void engine::exit()
{
}

void engine::initGame()
{
    /* Initialize the library */
    if (!glfwInit())
        return;

    /* Create a windowed mode window and its OpenGL context */
    window = new Window(640, 480, "Korbo Engine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return;
    }
    renderer = new Renderer(window);
     
}

void engine::gameLoop()
{
    while (!glfwWindowShouldClose(window->getWindow()))
    {
        renderer->BeginDrawing();
        update();
        renderer->EndDrawing();
    }
}

void engine::endGame()
{
    delete window;
    delete renderer;
    glfwTerminate();
}
