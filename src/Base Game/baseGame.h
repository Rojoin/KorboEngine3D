#pragma once
#include "Globals/dllHeader.h"
#include "Renderer/renderer.h"
#include "Shape/Shape.h"
#include "Window/window.h"


namespace Korbo
{
    class EXPORT engine
    {
    private:
        Renderer* renderer;
        Window* window;
        void initGame(int windowWhidth,int windowHeight);
        void endGame();
    
    public:
        engine(int windowWidth,int windowHeight);
        virtual ~engine();
        Renderer* getRenderer(); //TODO CAMBIAR POR Factory
        virtual void init();
        virtual void update();
        virtual void exit();
        void gameLoop();
    };
};
