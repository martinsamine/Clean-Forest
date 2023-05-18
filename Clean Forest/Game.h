#ifndef GAME_H
#define GAME_H
#include "Terrain.h"
#include "Player.h"
#include <iostream>

class Game
{

private:
    Terrain* T;
    Player* P1;
    bool s;
    bool p;
    bool a;
    int mode;
    int raio;

public:

    Game();
    void random();
    void window();
    void filehandler(std::string file, int op);
    void save();
    void load();
    void NewTerrain();
    void stats(); 
    void Autom();
    void Manual();
    void start();
    void pause();
    void simul();
    void AutoE();
    void Animation();
    bool empty()const;
    void exit();




};

#endif // GAME_H
