#pragma once
#include "Globals/dllHeader.h"

#include "Renderer/renderer.h"
#include "Shape/Shape.h"

#include "Window/window.h"
#include "Input/Input.h"
#include "Colitions/Colitions.h"
#include "Interface/Interface.h"
#include "Renderer/Frustrum.h"


namespace Korbo
{
    class EXPORT Engine
    {
    private:
        Renderer* renderer;
        Window* window;
        void initGame(int windowWhidth, int windowHeight);
        void endGame();
        float DeltaTime;
        float screenRatio;
        Interface interface;
    public:
        Engine(int windowWidth, int windowHeight);
        virtual ~Engine();
        Renderer* getRenderer(); 
        Camera* camera;
        Transform* root;
        virtual void init();
        virtual void update();
        virtual void exit();
        void gameLoop();
        void setLightPos(Vec3 position);
        void setAmbientLightStrengh(float value);
        void drawScene();
        float getDeltaTime();
        Transform* testTransform;
        Frustum* frustum = nullptr;
 
    protected:
        Input* input ;
    };
};

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
