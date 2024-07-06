#include "Engine.h"


#include "Globals/Time.h"
#include "Interface/Interface.h"
#include "Shape/Square.h"
#include "Shape/Triangle.h"

using namespace Korbo;

Camera* newCamera;
Window* currentWindow;
bool moveCamera = true;

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
    window = new Window(windowWhidth, windowHeight, "Korbo Engine 3D", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    camera = new Camera();

    newCamera = camera;
    currentWindow = window;
    renderer = new Renderer(window, camera);
    input = new Input(window->getWindow());
    glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window->getWindow(), mouse_callback);
    glfwSetScrollCallback(window->getWindow(), scroll_callback);
    glfwSetKeyCallback(window->getWindow(), key_callback);
    glfwSetFramebufferSizeCallback(window->getWindow(), framebuffer_size_callback);

    ImGui_ImplGlfw_InitForOpenGL(window->getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void Engine::gameLoop()
{
    while (!glfwWindowShouldClose(window->getWindow()))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Show a simple window
        {
            ImGui::Begin("Hello, World!"); // Create a window called "Hello, World!"
            ImGui::Text("This is some useful text."); // Display some text
            ImGui::End();
        }
        Time::setTime();
        DeltaTime = Time::getDeltaTime();
        renderer->BeginDrawing();
        camera->checkKeyboardMovement(window->getWindow());
        renderer->projection = camera->getProjectionMatrix(window->getWidth(), window->getHeight());
        renderer->view = camera->getViewMatrix();
        if (testTransform != nullptr)
        {
            Interface::ShowTransformEditor(testTransform);
        }
        ImGui::Render();
        update();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        renderer->EndDrawing();
    }
}

void Engine::setLightPos(Vec3 position)
{
    renderer->pointLight->position = glm::vec3(position.x, position.y, position.z);
}

void Engine::setAmbientLightStrengh(float value)
{
    renderer->ambientStrengh = glm::clamp(value, 0.0f, 1.0f);
}

float Engine::getDeltaTime()
{
    return DeltaTime;
}

void Engine::endGame()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
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
    if (moveCamera)
    {
        newCamera->checkMouseMovement(xoffset, yoffset);
    }
}

void scroll_callback(GLFWwindow* window, double xpos, double ypos)
{
    newCamera->checkMouseScroll(static_cast<float>(ypos));
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    currentWindow->SetWindowWidth(width);
    currentWindow->SetWindowHeight(height);
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
        newCamera->toggleCameraMode();
    if (key == GLFW_KEY_T && action == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        moveCamera = false;
    }
    if (key == GLFW_KEY_Y && action == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        moveCamera = true;
    }
}
