#include <conio.h>
#include "multiuse.h"
#include <stdlib.h>
#include <iostream>
#include <windows.h>

using namespace std;

void gotoxy(int x, int y)
{
    printf("%c[%d;%df", 0x1B, y, x);
}
void clrscr(void)
{
    system("clear");
}
void printbanner() {
    gotoxy(45, 1);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
    cout << "=========  =========  =========" << endl;
    gotoxy(45, 2);
    cout << "===        ===        ===      " << endl;
    gotoxy(45, 3);
    cout << "===        ======     =========" << endl;
    gotoxy(45, 4);
    cout << "===        ===              ===" << endl;
    gotoxy(45, 5);
    cout << "=========  ===        ========= " << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);



}

int menu() {

    printbanner();
    cout << "CFS is a planing and simulation software for cleaning forests(CLEAN FOREST SIMULATOR)," <<
        " or even to plan to clean a future electricity transportation line." << endl;

    gotoxy(45, 10);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
    cout << "MENU" << endl << endl;
    gotoxy(45, 16);
    cout << "1-NEW TERRAIN" << endl;
    gotoxy(45, 17);
    cout << "2-SAVE SIMULATION" << endl;
    gotoxy(45, 18);
    cout << "3-START SIMULATION" << endl;
    gotoxy(45, 19);
    cout << "4-ANIMATE SIMULATION" << endl;
    gotoxy(45, 20);
    cout << "5-LOAD SIMULATION" << endl;
    gotoxy(45, 21);
    cout << "6-HELP" << endl;
    gotoxy(45, 23);
    cout << "9-EXIT" << endl;

    return _getch();

}

void statscreen() {
    gotoxy(0, 33);
    for (int i = 0; i < 3; i++) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);
        for (int j = 0; j < 138; j++) {
            cout << '#';
        }
        cout << endl;
    }

    cout << "##########" << "             ######                 #############################" << endl;
    for (int i = 0; i < 3; i++) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);
        for (int j = 0; j < 138; j++) {
            cout << '#';
        }
        cout << endl;
    }
}

void help() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
    cout << "NEW TERRAIN" << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTBLUE);
    cout << "In this option you can create a terrain " << endl
        << "Homogeneous terrain, a terrain with only grass" << endl
        << "Random Terrain, terrain where the trees are put randomly, but with certain parameters that the users gives,"
        << "distance between trees, distance to the border, number of trees, not recomended putting distance between  trees 0,"
        << "because the program is trully random, it could place the trees together in the middle, or create a parcel of grass surrounded by trees that the robot cant access." << endl
        << "Alligned trees, under development" << endl<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
    cout << "START SIMULATION" << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTBLUE);
    cout << "In this option the user will run the simulation.First will be asked the insertion point of the machine in the terrain , "
        << "uses cordinates like (0,0), if the user gives coordinates bveyond the terrain the program"
        << "will ask again until it gives coordinates in the terrain." << endl
        << "In the next screen it will be asked the amount of moves per second the robot makes , but remember the robot is simulated at 1m/s." << endl
        << "Then the user will select the Simulation mode." << endl
        << "Automatic , the robot will run it self by starting at the lowest point possible of the terrain then will do it in a <snake> movement until it ends." << endl
        << "Automatic in Spiral, the robot will run itself starting at one of the sides of the terrain and will clean it in spiral." << endl
        << "Random, under development." << endl
        << "Manual, the robot is controlled by the user , can use ,WASD or arrows to command robot." << endl<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
    cout << "ANIMATION" << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTBLUE);
    cout << "In this robot will be animated all the moves the robot made until that moment." << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
    cout << "LOAD SIMULATION" << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTBLUE);
    cout << "In this option the user gives a name of the filein the samme manner of the option SAVE TERRAIN and the programm will read the file.It´s possible to create terrain with this files." << endl
        << "The symbols are " << endl << "*- TREE" << endl << "+-WALL OR OTHER OBSTACLE" << endl << ".-CUT GRASS" << endl << "X-TALL GRASS" << endl << "For any help contact me in github......"<<endl;


}