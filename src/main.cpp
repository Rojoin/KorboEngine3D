#include <GLFW/glfw3.h>
#include "Base Game/baseGame.h"

void main()
{
    engine* basegame = new engine();
    basegame->gameLoop();
    delete basegame;
}
