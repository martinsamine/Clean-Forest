#include "Game.h"
#include "multiuse.h"
#include "Terrain.h"
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Player.h"
#include <fstream>
#include <thread>
#include <iomanip>
#include <fstream>
#include <string>
/*
#include <crypto/aes.h>
#include <crypto/modes.h>
#include <crypto/files.h>
#include <crypto/filters.h>
#include <crypto/osrng.h>
#include <crypto/cryptlib.h>*/

using namespace std;
//using namespace CryptoPP;


Game::Game() {
    T = nullptr;
    P1 = nullptr;
    s = false;
    p = false;
    mode = 0;
    raio = 0;
    a = false;
}
bool Game::empty()const {

    if (T == nullptr)return true;

    return false;
}
void Game::save() {

    ofstream Myfile;
    string path = "Save/";
    string file;
    cin >> file;
    path += file;
    Myfile.open(path, ios::out |/*|ios::binary|*/ios::trunc);
    raio--;


    for (int i = 0; i < T->c; i++) {
        for (int j = 0; j < T->l; j++) {
            Myfile.put(T->map[i][j]);
        }
        Myfile << endl;
    }

    Myfile << 'P' << endl << mode;
    if (mode == 2)
        Myfile << ' ' << raio << endl;
    else
        cout << endl;
    if (mode == 0)return;
    Myfile << P1->moves << endl << P1->speed << endl;

    P1->atual = P1->head;
    Myfile << P1->atual->hx << ' ' << P1->atual->hy << ' ' << P1->atual->dir << endl;

    while (P1->retrace()) {
        Myfile << P1->x << ' ' << P1->y << ' ' << P1->direction << endl;
    }


    Myfile.close();

    cout << "Saved";

}
void Game::load() {
    ifstream Myfile;
    string path = "Save/";
    p = false;
    string file;
    string lin;
    cin >> file;
    path += file;
    Myfile.open(path, ios::in);
    int c = 0;
    int l = 0;

    if (!Myfile.is_open())
        cerr << "File not Found";

    getline(Myfile, lin);
    l = lin.length();
    if (l > 138) {
        cerr << "File not suported";
        Sleep(800);
        return;
    }
    while (lin != "P") {
        getline(Myfile, lin);
        c++;
        if (c > 30) {
            cerr << "File not suported";
            Sleep(800);
            return;
        }
    }


    if (T != nullptr) {
        delete T;
        delete P1;
    }

    T = new Terrain(l, c);
    Myfile.close();
    Myfile.open(path, ios::in);

    for (int i = 0; i < c; i++) {
        for (int j = 0; j < l; j++) {
            Myfile >> T->map[i][j];
            if (T->map[i][j] == cut)
                T->g++;
        }
    }
    getline(Myfile, lin);
    getline(Myfile, lin);
    T->printterrain();

    P1 = new Player;
    Myfile >> mode;
    if (mode == 0)
        return;
    if (mode == 2)
        Myfile >> raio;

    Myfile >> P1->moves;

    Myfile >> P1->speed;

    while (!Myfile.eof()) {


        Myfile >> P1->x >> P1->y >> P1->direction;
        P1->reg();

    }

    P1->x = P1->atual->hx;
    P1->y = P1->atual->hy;
    P1->direction = P1->atual->dir;


    Myfile.close();

}
void Game::NewTerrain() {
    mode = 0;
    int i = -1, j = -1, d;
    char o = '0';
    bool t = false;
    while (!t) {

        system("CLS");
        printbanner();
        cout << endl;
        cout << "Lenght of terrain(0-138):";
        cin >> i;
        cout << endl << "Widht of terrain(0-30): ";
        cin >> j;
        if ((j > 0 && j <= 30) && (i > 0 && i <= 138))
            t = true;


    }


    system("CLS");
    printbanner();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
    gotoxy(45, 16);
    cout << "1-HOMOGENEOUS TERRAIN" << endl;
    gotoxy(45, 17);
    cout << "2-RANDOM TERRAIN" << endl;
    gotoxy(45, 18);
    cout << "3-ALLIGNED TREES" << endl;
    while (o != '1' && o != '2' && o != '3')
        o = _getch();

    T = new Terrain(i, j);
    P1 = new Player;
    system("CLS");

    if (o == '1') {
        T->printterrain();
        system("pause");
    }
    else if (o == '2') {
        system("CLS");
        printbanner();
        cout << endl;
        cout << "Number of trees: ";
        cin >> i;
        cout << endl << "Distance between the trees: ";
        cin >> j;
        cout << endl << "Distance to the border: ";
        cin >> d;
        T->random(d, j, i);
        system("CLS");
        T->printterrain();
        cout << endl;
        system("pause");
    }
}
void Game::start() {
    bool quit = false;
    int op;
    thread* t;
    char o;
    window();


    while (!quit) {

        system("CLS");
        op = menu();
        system("CLS");
        if (op == '1') {
            cout << "NEW TERRAIN" << endl;


            NewTerrain();
        }
        else if (op == '2') {
            if (empty()) {
                cout << "CREATE TERRAIN OR LOAD SIMULATION TO SAVE";
                Sleep(300);
            }
            else {
                cout << "INPUT FILE NAME" << endl;
                save();
            }
        }

        else if (op == '3') {
            cout << "LOADING..." << endl;
            if (empty()) {

                cout << "NO TERRAIN LOADED" << endl;

            }
            else
                simul();


        }

        else if (op == '4') {
            if (!empty()) {


                a = false;

                cout << "DRAWING.." << endl;

                Sleep(300);
                system("CLS");

                t = new thread(&Game::Animation, this);

                while (!a) {

                    o = _getch();
                    if (o == 'q' || o == 'Q') {
                        a = true;

                    }

                    else if (o == 't' || o == 'T') {
                        if (!T->trail)
                            T->trail = true;
                        else
                            T->trail = false;
                    }
                }
                t->join();
                t->~thread();
                delete t;

                while (P1->retrace()) {
                    T->trail = true;
                    T->update(P1->y, P1->x);

                }
                T->trail = false;
            }
            else {
                cout << "NO TERRAIN LOADED" << endl;
                system("pause");
            }

        }


        else if (op == '5') {
            cout << "INPUT FILE NAME" << endl;
            load();

            if (!empty()) {
                system("CLS");
                T->printterrain();
            }
            system("pause");
        }
        else if (op == '6') {
            help();
            system("pause");
        }
        else if (op == '9')
            return;
        Sleep(500);
        op = 0;
    }

}
void Game::Autom() {

    bool desvio = false;
    bool right = false;


    int verifier = T->c * T->l;
    verifier -= T->t;
    char o;
    Sleep(1000);


    if (mode == 0) {

        mode = 1;
        if (P1->x != 0) {

            while (P1->x != 0 && !p) {
                stats();

                if (T->map[P1->y][P1->x - 1] == trees) {

                    if (T->map[P1->y - 1][P1->x] == trees || T->map[P1->y - 1][P1->x] == wall || P1->y == 0) {
                        T->update(P1->y, P1->x);
                        P1->move('s');
                    }
                    else {
                        T->update(P1->y, P1->x);
                        P1->move('w');
                    }
                }
                T->update(P1->y, P1->x);
                P1->move('a');

            }
        }
        if (P1->y != T->c - 1) {

            while (P1->y != T->c - 1 && !p) {
                stats();
                if (T->map[P1->y + 1][P1->x] == trees) {

                    if (T->map[P1->y][P1->x - 1] == trees || T->map[P1->y][P1->x - 1] == wall || P1->x == 0) {
                        T->update(P1->y, P1->x);
                        P1->move('d');

                    }
                    else {
                        T->update(P1->y, P1->x);
                        P1->move('a');

                    }
                }
                T->update(P1->y, P1->x);
                P1->move('s');

            }
        }

        T->update(P1->y, P1->x);
    }
    else if (P1->direction == '<') {
        right = true;
    }



    while (verifier > T->g && !p) {
        stats();

        if (desvio && T->map[P1->y + 1][P1->x] != trees && T->map[P1->y + 1][P1->x] != wall) {
            desvio = false;
            T->update(P1->y, P1->x);
            P1->move('s');
        }



        if (right) {
            if ((T->map[P1->y][P1->x - 1] == trees || T->map[P1->y][P1->x - 1] == wall) && P1->y != 0) {
                T->update(P1->y, P1->x);
                P1->move('w');

                desvio = true;
            }
            T->update(P1->y, P1->x);
            P1->move('a');

        }
        else if (!right) {
            if ((T->map[P1->y][P1->x + 1] == trees || T->map[P1->y][P1->x + 1] == wall) && P1->y != 0) {
                T->update(P1->y, P1->x);
                P1->move('w');

                desvio = true;

            }
            T->update(P1->y, P1->x);
            P1->move('d');

        }

        if (desvio && T->map[P1->y + 1][P1->x] != trees && T->map[P1->y + 1][P1->x] != wall) {
            desvio = false;
            T->update(P1->y, P1->x);
            P1->move('s');
        }


        if (P1->x == T->l - 1 && P1->y != 0) {
            T->update(P1->y, P1->x);
            P1->move('w');

            right = true;
        }



        else if (P1->x == 0 && P1->y != 0) {
            T->update(P1->y, P1->x);
            P1->move('w');

            right = false;
        }





    }

    if (!p)
        system("pause");
    else if (p) {
        system("CLS");
        cout << "Pause";
    }
    if (verifier <= T->g && !p)
    s = true;
    system("Pause");

}
void Game::stats() {

    int m = P1->moves / 60;
    int s = P1->moves % 60;
    int h = m / 60;
    m = m % 60;
    int a = T->l * T->c;
    a -= T->t;

    gotoxy(2, 36);


    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), MAGENTA);
    cout << "Time:" << setw(2) << h << ":" << setw(2) << m << ":" << setw(2) << s;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);
    cout << "####";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), MAGENTA);
    cout << "Cut Grass: " << setw(7) << T->g;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);
    cout << "##";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), MAGENTA);
    cout << "Area to be clean:" << setw(7) << a - T->g;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);
    cout << "##";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), MAGENTA);
    cout << "Area of obstacles:" << setw(7) << T->t;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);
    cout << "##";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), MAGENTA);
    cout << "Total Area : " << setw(7) << T->l * T->c;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);
    cout << "##";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), MAGENTA);
    cout << "Total Moves : " << setw(7) << P1->moves;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);
    cout << "####";






}
void Game::Manual()
{

    s = false;
    mode = 4;
    int c = 0;
    int i = 0;

    while (!s && !p) {
        c = _getch();
        stats();

        if ((c == KEY_UP || c == 'w' || c == 'W') && (P1->y != 0)) {

            if ((T->map[P1->y - 1][P1->x] == grass || T->map[P1->y + 1][P1->x] == cut)) {
                P1->move('w');
                T->update(P1->y+1, P1->x);
            }

        }



        else if ((c == KEY_DOWN || c == 'S' || c == 's') && P1->y != T->c - 1) {


            if ((T->map[P1->y + 1][P1->x] == grass || T->map[P1->y + 1][P1->x] == cut)) {

               
                P1->move('s');
                T->update(P1->y-1, P1->x);

            }
        }

        else if ((c == KEY_LEFT || c == 'a' || c == 'A') && P1->x != 0) {




            if ((T->map[P1->y][P1->x - 1] == grass || T->map[P1->y][P1->x - 1] == cut)) {

                
                P1->move('a');
                T->update(P1->y, P1->x+1);

            }
        }


        else if ((c == KEY_RIGHT || c == 'D' || c == 'd') && P1->x < T->l) {

            if ((T->map[P1->y][P1->x + 1] == grass || T->map[P1->y][P1->x + 1] == cut)) {

                
                P1->move('d');
                T->update(P1->y, P1->x-1);
            }
        }

        else if (c == 'q' || c == 'Q') { p = true; }

        else if (c == 't' || c == 'T') {
            if (!P1->track){
                T->trail = true;
                P1->track = true;
                }
            else{
                T->trail = false;
                P1->track = false;
            }
            }



        system("Pause");


    }

}
void Game::AutoE() {



    bool sides = false;
    bool desvio = false;
    bool right = false;
    bool up = false;
    bool esp = false;
    const int  la = T->l;
    const int  co = T->c;
    bool** done;
    int verifier = T->c * T->l;
    verifier -= T->t;
    done = new bool* [la];

    for (int j = 0; j < la; j++) {
        done[j] = new bool[co];
    }

    if (mode != 2) {
        mode = 2;
        raio = 1;
        if (P1->y == 0) {
            up = true;
        }

        for (int j = 0; j < T->l; j++) {

            for (int k = 0; k < T->c; k++) {
                done[j][k] = false;
            }

        }


        if (P1->x != 0 && P1->x != T->l - 1 && !p) {

            


            if (P1->x < T->l / 2) {


                while (P1->x != 0 && !p) {
                    stats();
                    if (T->map[P1->y][P1->x - 1] == trees || T->map[P1->y][P1->x - 1] == wall) {

                        T->update(P1->y, P1->x);
                        P1->move('w');

                    }

                    T->update(P1->y, P1->x);
                    P1->move('a');
                }


                


                right = false;
                sides = true;

            }


            else if (P1->x > T->l / 2) {

                while (P1->x != T->l - 1 && !p) {
                    stats();
                    if (T->map[P1->y][P1->x + 1] == trees || T->map[P1->y][P1->x + 1] == wall) {


                        T->update(P1->y, P1->x);
                        P1->move('w');


                    }
                    T->update(P1->y, P1->x);
                    P1->move('d');

                }
                right = true;
                sides = true;
            }


        }

        done[P1->x][P1->y] = true;

    }

    else {
        P1->atual = P1->head;
        while (P1->retrace())
            done[P1->x][P1->y] = true;

        if (P1->direction == '>') {
            up = true;
            sides = false;
        }
        else if (P1->direction == '<') {
            up = false;
            sides = false;
        }
        else if (P1->direction == '^') {
            up = false;
            sides = true;
            right = false;
        }
        else if (P1->direction == 'v') {
            up = false;
            sides = true;
            right = true;
        }
    }

    while (verifier > T->g && !p) {

        while (!esp && !p) {
            stats();
            if (right && sides && !p) {

                while (P1->y < T->c - raio && !p) {
                    stats();
                    if (done[P1->x][P1->y + 1]&&!desvio) {
                        done[P1->x][P1->y] = true;
                        esp = true;
                        break;
                    }

                    if (desvio && T->map[P1->y][P1->x + 1] != trees && T->map[P1->y][P1->x + 1] != wall) {
                        desvio = false;
                        T->update(P1->y, P1->x);
                        P1->move('d');


                    }

                    if ((T->map[P1->y + 1][P1->x] == trees || T->map[P1->y + 1][P1->x] == wall)) {
                        T->update(P1->y, P1->x);
                        P1->move('a');

                        desvio = true;
                    }


                    T->update(P1->y, P1->x);
                    P1->move('s');
                    if (!desvio)done[P1->x][P1->y] = true;


                }


                if (!esp) {
                    right = false;
                    up = false;
                    sides = false;
                }

                if (desvio && T->map[P1->y][P1->x + 1] != trees && T->map[P1->y][P1->x + 1] != wall) {

                    T->update(P1->y, P1->x);
                    P1->move('d');
                    T->update(P1->y, P1->x);
                    P1->move('a');
                    done[P1->x][P1->y] = true;
                }

                desvio = false;

            }

            else if (!right && sides && !p) {

                while (P1->y > raio - 1 && !p) {
                    stats();
                    if (done[P1->x][P1->y - 1]&&!desvio) {
                        done[P1->x][P1->y] = true;
                        esp = true;
                        break;
                    }

                    if (desvio && T->map[P1->y][P1->x - 1] != trees && T->map[P1->y][P1->x - 1] != wall) {
                        desvio = false;
                        T->update(P1->y, P1->x);
                        P1->move('a');


                    }
                    if ((T->map[P1->y - 1][P1->x] == trees || T->map[P1->y - 1][P1->x] == wall)) {
                        T->update(P1->y, P1->x);
                        P1->move('d');

                        desvio = true;
                    }

                    T->update(P1->y, P1->x);
                    P1->move('w');
                    if (!desvio)done[P1->x][P1->y] = true;

                }
                if (!esp) {
                    right = false;
                    up = true;
                    sides = false;
                }

                if (desvio && T->map[P1->y + 1][P1->x] != trees && T->map[P1->y + 1][P1->x] != wall) {

                    T->update(P1->y, P1->x);
                    P1->move('a');
                    T->update(P1->y, P1->x);
                    P1->move('d');
                    done[P1->x][P1->y] = true;
                }

                desvio = false;
            }

            else if (up && !sides && !p) {

                while (P1->x != T->l - raio)
                {
                    stats();
                    if (done[P1->x + 1][P1->y]&&!desvio) {
                        done[P1->x][P1->y] = true;
                        esp = true;
                        break;
                    }


                    if (desvio && T->map[P1->y - 1][P1->x] != trees && T->map[P1->y - 1][P1->x] != wall) {
                        desvio = false;
                        T->update(P1->y, P1->x);
                        P1->move('w');


                    }
                    if ((T->map[P1->y][P1->x + 1] == trees || T->map[P1->y][P1->x + 1] == wall)) {
                        T->update(P1->y, P1->x);
                        P1->move('s');

                        desvio = true;
                    }

                    T->update(P1->y, P1->x);
                    P1->move('d');
                    if (!desvio)done[P1->x][P1->y] = true;
                }




                if (desvio && T->map[P1->y + 1][P1->x] != trees && T->map[P1->y + 1][P1->x] != wall) {

                    T->update(P1->y, P1->x);
                    P1->move('w');
                    T->update(P1->y, P1->x);
                    P1->move('s');
                    done[P1->x][P1->y] = true;
                }

                desvio = false;



                if (!esp) {
                    right = true;
                    up = false;
                    sides = true;
                }
            }


            else if (!up && !sides && !p) {

                while (P1->x > raio - 1 && !p) {
                    stats();
                    if (done[P1->x - 1][P1->y]&&!desvio) {
                        done[P1->x][P1->y] = true;
                        esp = true;
                        break;
                    }


                    if (desvio && T->map[P1->y + 1][P1->x] != trees && T->map[P1->y + 1][P1->x] != wall) {
                        desvio = false;
                        T->update(P1->y, P1->x);
                        P1->move('s');


                    }
                    if ((T->map[P1->y][P1->x - 1] == trees || T->map[P1->y][P1->x - 1] == wall)) {
                        T->update(P1->y, P1->x);
                        P1->move('w');

                        desvio = true;
                    }


                    T->update(P1->y, P1->x);
                    P1->move('a');
                    if (!desvio)done[P1->x][P1->y] = true;

                }


                if (desvio && T->map[P1->y + 1][P1->x] != trees && T->map[P1->y + 1][P1->x] != wall && !p) {

                    T->update(P1->y, P1->x);
                    P1->move('s');
                    T->update(P1->y, P1->x);
                    P1->move('w');
                }

                desvio = false;

                if (!esp & !p) {
                    sides = true;
                }


            }
        }



        esp = false;

        if (right && sides) {
            T->update(P1->y, P1->x);
            P1->move('s');


        }
        else if (!right && sides) {
            Sleep(1);
            T->update(P1->y, P1->x);
            P1->move('d');


        }
        else if (up && !sides) {
            T->update(P1->y, P1->x);
            P1->move('s');


        }
        else if (!up && !sides) {
            T->update(P1->y, P1->x);
            P1->move('w');

        }
        raio++;
        stats();
    }
    if(verifier <= T->g && !p)
    s = true;

    stats();
}
void Game::Animation() {
   
    system("CLS");
    cout << "Press Q to quit and press T for track";
    Sleep(1100);
    system("CLS");
    T->revert();
    T->printterrain();
    P1->atual = P1->head;
    P1->x = P1->atual->hx;
    P1->y = P1->atual->hy;
    P1->direction = P1->atual->dir;

    P1->draw();
    Sleep(500);
    T->update(P1->y, P1->x);

    while (P1->retrace() && !a) {
        P1->draw();
        Sleep(1000 / P1->speed);
        T->update(P1->y, P1->x);
    }
    a = true;
}
void Game::simul() {

    char o= '#';
    p = false;
    unsigned int x[2];
    unsigned int speed = 0;
    bool temp = false;
    thread* t;


    if (mode == 0) {
        
        delete P1;
      
        while (!temp) {
            system("CLS");
            printbanner();
            cout << endl << "Entry point:" << endl;
            cin >> x[0] >> x[1];
            if (x[0] < T->l && x[1]< T->c)
                temp = true;
        }
        while (!speed > 0) {
            system("CLS");
            printbanner();
            cout << endl << "Velocity in m/s:" << endl;
            cin >> speed;
        }
        P1 = new Player(x[0], x[1], speed);


        system("pause");

        system("CLS");
        printbanner();
        cout << "Operating mode" << endl;
        gotoxy(45, 15);
        cout << "1-Automatic";
        gotoxy(45, 16);
        cout << "2-Automatic in Spiral";
        gotoxy(45, 17);
        cout << "3-Random";
        gotoxy(45, 18);
        cout << "4-Manual";
        o = _getch();
    }
    else if (mode != 0) {
        cout << "Keep simulation running with the same settings?"<<endl;

            while (o != 'y' && o != 'N' && o != 'Y' && o != 'n')
                o = _getch();
            if ( o == 'y' || o == 'Y')
                o == mode;
            else if (o == 'n' || o == 'N') {
                delete P1;
                while (!temp) {
                    system("CLS");
                    printbanner();
                    cout << endl << "Entry point:" << endl;
                    cin >> x[0] >> x[1];
                    if (x[0] < T->l && x[1] < T->c)
                        temp = true;
                }
                while (!speed > 0) {
                    system("CLS");
                    printbanner();
                    cout << endl << "Velocity in m/s:" << endl;
                    cin >> speed;
                }
                P1 = new Player(x[0], x[1], speed);

            }
    }
    system("CLS");
    cout << "Press Q to quit and press T for track";
    Sleep(1100);
    system("CLS");
    T->printterrain();
    P1->draw();
    statscreen();



    if (o == '1' || mode == 1) {
        t = new thread(&Game::Autom, this);
        p = false;
        while (!p && !s) {

            o = _getch();

            if (o == 'q' || o == 'Q') {
                p = true;

            }

            else if (o == 't' || o == 'T') {
                if (!T->trail) {
                    T->trail = true;
                    P1->track = true;
                }
                else {
                    T->trail = false;
                    P1->track = false;
                }
            }

            else
                p = false;
        }


        t->join();
        t->~thread();
        delete t;
    }
    else if (o == '2' || mode == 2) {
        t = new thread(&Game::AutoE, this);
        while (!p && !s) {

            o = _getch();
            if (o == 'q' || o == 'Q') {
                p = true;

            }

            else if (o == 't' || o == 'T') {
                if (!T->trail){
                    T->trail = true;
                P1->track = true;
                }
                else{
                    T->trail = false;
                P1->track = false;
                }
            }
        }

        t->join();
        t->~thread();
        delete t;
    }
    else if (o == '3' || mode == 3)cout << "Random";


    else if (o == '4' || mode == 4) {
        Manual();

    }

    if (p) {
        system("CLS");
        cout << "Do you wanna save simulation in file?" << endl << "Y/N";
        o = _getch();
        if (o == 'Y' || o == 'y') {
            system("CLS");
            cout << "Input name of file and extension" << endl;
            save();
        }
        else if (o == 'N' || o == 'n') {
            system("CLS");
            cout << "If the program is closed without saving simulation you will lose it" << endl;
            Sleep(100);
        }

    }


}
void Game::window() {



    HWND hwnd;
    HANDLE hout;
    SetConsoleTitleA("CFS");
    Sleep(100);
    hwnd = FindWindowA(NULL, "CFS");
    MoveWindow(hwnd, 0, 0, 1500, 800, TRUE);
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.bVisible = 0;
    info.dwSize = 1;
    SetConsoleCursorInfo(hout, &info);

}
    /*
    void Game::filehandler(string file, int op) {

        string pass = "Yoolo";

        SecByteBlock encryptionKey(reinterpret_cast<const CryptoPP::byte*>(pass.data()), AES::DEFAULT_KEYLENGTH);


        if(op==1){
            ifstream temp("Save/temp.txt", ios::binary);
            ofstream Myfile(file, ios::binary | ios::trunc);
        CBC_Mode<AES>::Encryption encryption;
        encryption.SetKeyWithIV(encryptionKey, AES::DEFAULT_KEYLENGTH, encryptionKey);

        // Open input and output files
        FileSource(temp, true,
                   new StreamTransformationFilter(encryption , new FileSink(Myfile))
                   );
        }
        else if (op == 0) {
        ifstream Myfile(file, ios::binary);
        ofstream temp("Save/temp", ios::binary | ios::trunc);
            // Set up AES decryption algorithm in CBC mode
            CBC_Mode<AES>::Decryption decryption;
            decryption.SetKeyWithIV(encryptionKey, AES::DEFAULT_KEYLENGTH, encryptionKey);

            // Decrypt Myfile to temp file
            FileSource(Myfile, true,
                       new StreamTransformationFilter(
                           decryption, new FileSink(temp) )
                       );
        }
    }*/
void Game::random() {

    srand(time(NULL));
    P1->x = rand() % T->l;
    P1->y = rand() % T->c;






}


