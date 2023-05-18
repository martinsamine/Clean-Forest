#pragma comment(lib, "winmm.lib")
#include "Player.h"
#include <stdlib.h>
#include <iomanip>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <time.h>
#include "multiuse.h"
#include <mmsystem.h>



using namespace std;




Player::Player()
{
    x = 0;
    y = 0;
    direction = '>';
    moves = 0;
    speed = 1;
    head = nullptr;
    atual = nullptr;
    track = false;

}
Player::Player(int xx, int yy, int spedd)
{
    x = xx;
    y = yy;
    direction = '>';
    moves = 0;
    speed = spedd;
    head = nullptr;
    atual = nullptr;
    track = false;


}
void Player::draw() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARKGRAY);

    COORD point;
    point.X = x + 1;
    point.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);

    cout << BS << direction;

}

void Player::move(int c) {


    int ping=0;

    reg();
    

    if (c == 'w') {

        if (direction == '<' || direction == '>') {
            moves++;
            ping = 1;
            
        }
        else if (direction == 'v') {
            moves += 2;
            ping = 2;
           
       
        }

        direction = '^';
        draw();
        Sleep((1000 / speed)*ping);
        if(!track)
        cout << BS << cut;
        
        y--;
        moves++;

        draw();
        Sleep(1000 / speed);
        PlaySound(TEXT("Grass.wav"), NULL, SND_ASYNC);

    }
    else if (c == 's') {
        if (direction == '<' || direction == '>') {
            ping = 2;
            moves++;
        }
        else if (direction == '^') {
            ping = 3;
            moves += 2;
        }

        direction = 'v';
        draw();
        Sleep((1000 / speed) * ping);
        if (!track)
        cout << BS << cut;
        y++;

        moves++;
        draw();
        Sleep(1000 / speed);
        PlaySound(TEXT("Grass.wav"), NULL, SND_ASYNC);

    }
    else if (c == 'a') {
        if (direction == '^' || direction == 'v') {
            ping = 1;
            moves++;
        }
        else if (direction == '>') {
            ping = 2;
            moves += 2;
        }

        direction = '<';
        draw();
        Sleep((1000 / speed) * ping);
        if (!track)
        cout << BS << cut;
        x--;
        moves++;
        draw();
        Sleep(1000 / speed);
        PlaySound(TEXT("Grass.wav"), NULL, SND_ASYNC);
    }
    else if (c == 'd') {
        if (direction == '^' || direction == 'v') {
            ping = 1;
            moves++;
        }
        else if (direction == '<') {
            ping = 2;
            moves += 2;
        }

        direction = '>';
        draw();
        Sleep((1000 / speed) * ping);
        if (!track)
        cout << BS << cut;
        x++;
        moves++;
        draw();
        Sleep(1000 / speed);
        PlaySound(TEXT("Grass.wav"), NULL,SND_FILENAME|| SND_ASYNC);
    }



}

void Player::reg() {

    regmove* n = new regmove;

    n->hx = x;
    n->hy = y;
    n->dir = direction;
    n->next = nullptr;

    if (head == nullptr) {

        head = new regmove;
        head = n;
        atual = head;
        return;
    }

    else {


        atual->next = n;
        atual = atual->next;

    }
}

bool Player::retrace() {



    if (head == nullptr)
        return false;
    if (atual->next == nullptr)
        return false;
    atual = atual->next;

    x = atual->hx;
    y = atual->hy;
    direction = atual->dir;

    return true;

}