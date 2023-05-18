#include "Terrain.h"
#include "multiuse.h"
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <time.h>
#include <math.h>

using namespace std;


bool distance(int** pt, int x, int y, int d, int max) {//funcao para calcular distancia , suporte para random and alligned

    int i = 0;
    double t;
    if (pt[0][0] == -1) { return true; }
    else {
        while (pt[i][0] != -1 && i < max - 1) {
            t = pow(pt[i][0] - x, 2);
            t += pow(pt[i][1] - y, 2);
            t = sqrt(t);
            t--;

            if (t < d) {
                return false;
            }
            i++;
        }
        return true;
    }



}
Terrain::Terrain(int dl, int dc)//construtor Terrain
{
    t = 0;
    g = 0;
    c = dc;
    l = (dl);
    trail = false;
    map = new char* [c];
    for (int i = 0; i < c; i++) {
        map[i] = new char[l];
    }
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < l; j++) {
            map[i][j] = 'X';
        }

    }



}
void Terrain::update(int i, int j) {//quando simulacao corre , este metodo esta responsavel por atualizar o terreno
    if (map[i][j] != cut)g++;
    map[i][j] = cut;

    if (!trail) {
        COORD point;
        point.X = j + 1;
        point.Y = i;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
        cout << BS << cut;
    }


}
void Terrain::random(int ld, int td, int nt) {//random
    int x = 0;
    int y = 0;
    int i = 0;
    int v = l * c;
    srand(time(NULL));

    int** d = new int* [nt];//tabela bidemensional que representa o terreno de modo a sabe rse tem arvores

    for (int i = 0; i < nt; i++) {
        d[i] = new int[2];
        d[i][0] = -1;
        d[i][1] = -1;
    }

    while (t < nt && i < v) {//verifica se ja meteu todas as arvores , max de tentativas corrersponde a area do terreno

        x = rand() % l;
        y = rand() % c;
        if (distance(d, y, x, td, nt) && x > ld && (l - x) > ld && y > ld && (c - y) > ld && t < nt) {


            map[y][x] = trees;
            d[t][0] = y;
            d[t][1] = x;
            t++;


        }
        i++;
    }



    for (int i = 0; i < nt; i++) {
        delete[] d[i];
    }

    delete[] d;


}
//void Terrain::alligned(int dc, int dl) {



void Terrain::printterrain() const {




    for (int i = 0; i < c; i++) {
        for (int j = 0; j < l; j++) {

            if (map[i][j] == trees)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CT);

            else if (map[i][j] == grass)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);


            else if (map[i][j] == wall)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);

            else if (map[i][j] == cut)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGREEN);

            cout << map[i][j];
        }
        cout << endl;
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);

}
void Terrain::revert() {//para animar simulacao


    for (int i = 0; i < c; i++) {
        for (int j = 0; j < l; j++) {
            if (map[i][j] == cut)
                map[i][j] = grass;

        }
    }





}



