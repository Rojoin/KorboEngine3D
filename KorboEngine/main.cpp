#include <GLFW/glfw3.h>
#include "baseGame.h"

int main(void)
{
    Game* basegame = new Game();
    basegame->gameLoop();
    delete basegame;
    

    return 0;
}
