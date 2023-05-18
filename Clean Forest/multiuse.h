#pragma once
#ifndef MULTIUSE_H
#define MULTIUSE_H

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define trees '*'
#define cut '.'
#define grass 'X'
#define wall '+'
const char BS = 8;
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15
#define CT 138

void gotoxy(int x, int y);

void clrscr(void);

void printbanner(void);
int menu();
void statscreen();
void help();

#endif // MULTIUSE_H
