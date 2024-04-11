#include "Engine.h"

#include "Globals/Time.h"
#include "Shape/Square.h"
#include "Shape/Triangle.h"

using namespace Korbo;

Camera* newCamera;

Engine::Engine(int windowWidth, int windowHeight)
{
    initGame(windowWidth, windowHeight);
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

void Engine::initGame(int windowWhidth, int windowHeight)
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

    camera = new Camera();

    newCamera = camera;

    renderer = new Renderer(window, camera);
    input = new Input(window->getWindow());
    glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window->getWindow(), mouse_callback);
    glfwSetScrollCallback(window->getWindow(), scroll_callback);
    glfwSetKeyCallback(window->getWindow(), key_callback);
}

void Engine::gameLoop()
{
    while (!glfwWindowShouldClose(window->getWindow()))
    {
        Time::setTime();
        DeltaTime = Time::getDeltaTime();
        renderer->BeginDrawing();
        camera->checkKeyboardMovement(window->getWindow());
        renderer->projection = camera->getProjectionMatrix(window->getWidth(), window->getHeight());
        renderer->view = camera->getViewMatrix();
        update();
        renderer->EndDrawing();
    }
}

void Engine::setLightPos(Vec3 position)
{
    renderer->lightPos = glm::vec3(position.x,position.y,position.z);
}

void Engine::setAmbientLightStrengh(float value)
{
    renderer->ambientStrengh = glm::clamp(value,0.0f,1.0f);
}

float Engine::getDeltaTime()
{
    return DeltaTime;
}

void Engine::endGame()
{
    delete window;
    delete renderer;
    delete camera;
    glfwTerminate();
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (newCamera->firstMouse)
    {
        newCamera->lastX = xpos;
        newCamera->lastY = ypos;
        newCamera->firstMouse = false;
    }

    float xoffset = xpos - newCamera->lastX;
    float yoffset = newCamera->lastY - ypos;

    newCamera->lastX = xpos;
    newCamera->lastY = ypos;
    newCamera->checkMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xpos, double ypos)
{
    newCamera->checkMouseScroll(static_cast<float>(ypos));
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
        newCamera->toggleCameraMode();
    
}
