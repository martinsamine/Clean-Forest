#include "multiuse.h"
#include "Game.h"
#include <iostream>
#include "Terrain.h"
#include "Player.h"


int main()
{
    Game CFS;
    CFS.start();
    system("CLS");
    std::cout << "BYE" << std::endl;
    Sleep(1000);
    return 0;
}
