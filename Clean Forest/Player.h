#ifndef PLAYER_H
#define PLAYER_H
#include "Terrain.h"
#include<windows.h>



class regmove {

public:
    int hx;
    int hy;
    char dir;
    regmove* next;
};

class Player
{
private:
    //COORD console;
    int x;
    int y;
    char direction;
    int moves;
    int speed;
    bool track;
    regmove* head;
    regmove* atual;
    // HWND hwnd;
    // COORD co;

public:
    Player();
    Player(int xx, int yy, int speed);
    void  draw();
    void move(int c);
    void reg();
    bool retrace();

    friend class Game;
    friend class Terrain;
};



#endif // PLAYER_H

