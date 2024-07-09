#include "Engine.h"
#include "Globals/Time.h"
#include "Interface/Interface.h"
#include "Mesh/Model.h"
#include "Renderer/BoundingVolumes.h"
//#include "Renderer/Frustrum.h"


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
    root = new Transform(nullptr, glm::vec3(0), glm::vec3(0), glm::vec3(1));
    //testTransform2 = new Frustum();
    root->name = "Root";
    screenRatio = windowWhidth / windowHeight;
    frustum = new Frustum(Frustum::createFrustumFromCamera(camera, screenRatio,glm::radians(camera->Zoom), NEAR_PLANE, FAR_PLANE-500));
    view = camera->getProjectionMatrix(window->getWidth(), window->getHeight());
    newCamera = camera;
    currentWindow = window;
    renderer = new Renderer(window, camera);
    input = new Input(window->getWindow());

#pragma region CallBacks
    glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window->getWindow(), mouse_callback);
    glfwSetScrollCallback(window->getWindow(), scroll_callback);
    glfwSetKeyCallback(window->getWindow(), key_callback);
    glfwSetFramebufferSizeCallback(window->getWindow(), framebuffer_size_callback);
#pragma endregion
#pragma  region ImGui
    ImGui_ImplGlfw_InitForOpenGL(window->getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");
#pragma  endregion
}

void Engine::gameLoop()
{
    while (!glfwWindowShouldClose(window->getWindow()))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Korbo Engine Init!");
            ImGui::Text(
                "Move with WASD. Press T to lock the mouse and Y to use it as firstPerson Camera. Press R* for ThirdPersonMode");
            ImGui::End();
        }
        Time::setTime();
        DeltaTime = Time::getDeltaTime();
        renderer->BeginDrawing();
        camera->checkKeyboardMovement(window->getWindow());
        renderer->projection = camera->getProjectionMatrix(window->getWidth(), window->getHeight());
        renderer->view = camera->getViewMatrix();

        interface.ShowTransformEditor(root);
        ImGui::Render();
        update();
       // frustum = new Frustum(Frustum::createFrustumFromCamera(camera, screenRatio,glm::radians(camera->Zoom), NEAR_PLANE, FAR_PLANE-500));
        drawScene();
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

void Engine::drawScene()
{
    for (auto child : root->childs)
    {
        if (child->entity != nullptr)
        {
            Model* entity = dynamic_cast<Model*>(child->entity);
            if (entity != nullptr)
            {
               // std::vector<glm::vec3> vertices = entity->getGlobalAABB().getVertice();
               // renderer->DrawLinesAABB(entity->tranform->modelWorld, vertices);

                entity->generateAABB();
               entity->DrawWithFrustum(frustum);
               // child->entity->Draw();
            }
            else
            {
              //  
            }
        }
    }
    renderer->DrawFrustum(view);
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
    //  delete frustum;
    delete frustum;
    delete window;
    delete input;
    delete renderer;
    delete camera;
    delete root;
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
    if (moveCamera)
    {
        newCamera->checkMouseScroll(static_cast<float>(ypos));
    }
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
    if (key == GLFW_MOUSE_BUTTON_2 && action == GLFW_REPEAT && !moveCamera)
    {
        moveCamera = true;
        if (key == GLFW_MOUSE_BUTTON_2 && action == GLFW_RELEASE)
        {
            moveCamera = false;
        }
    }
}
