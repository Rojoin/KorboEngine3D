#include <GLFW/glfw3.h>
#include "baseGame.h"

int main(void)
{
    engine* basegame = new engine();
    basegame->gameLoop();
    delete basegame;
   
    return 0;
}
