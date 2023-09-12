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
		void initGame();
		void endGame();
		Shape* shape;
	public:
		 engine();
			~engine();
		 void gameLoop();

	};

};

