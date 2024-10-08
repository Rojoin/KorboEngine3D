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
        void CalculateTargetPlanes();
        float DeltaTime;
        float screenRatio;
        Transform* bspTarget;
        Interface interface;
        bool showDebug = false;
        vector<Plane> bspPlanes;
        vector<bool> planesToCheck;
    //    list<bool> bspTargetDirections ={};
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
        Frustum frustum;
        glm::mat4x4 view;
        void addPlaneToBSP(Plane plane);
        void addPlaneToBSP(glm::vec3 point,glm::vec3 normal);
    
        
 
    protected:
        Input* input ;
    };
};

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
