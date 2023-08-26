#include "Base Game/baseGame.h"

void main()
{
    engine* basegame = new engine();
    basegame->gameLoop();
    delete basegame;
}
