/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
 */

#include <string.h>

#include "keyboard.h"
#include "screen.h"
#include "timer.h"
#include "walls.h"

int pacmanX = 34, pacmanY = 12;
int incX = 1, incY = 1;
#define PACMAN 'P'

void printChar(char c, int nextX, int nextY) {
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(pacmanX, pacmanY);
    printf(" ");
    screenGotoxy(pacmanX, pacmanY);
    printf("%c", c);
}

enum direction {
    DIR_W = 119,
    DIR_A = 97,
    DIR_S = 115,
    DIR_D = 100
};

void moveChar(int *newX, int *newY, int d, char c) {
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(*newX, *newY);
    switch (d) {
        case DIR_W:
            if(walls[*newX][*newY-1] == 1){
                return;
            };
            printf(" ");
            *newY = (*newY - incY < MINY + 1) ? MINY + 1 : *newY - incY;
            break;
        case DIR_A:
            if(walls[*newX-1][*newY] == 1){
                return;
            };
            printf(" ");
            *newX = (*newX - incX < MINX + 1) ? MINX + 1 : *newX - incX;
            break;
        case DIR_S:
            if(walls[*newX][*newY+1] == 1){
                return;
            };
            printf(" ");
            *newY = (*newY + incY > MAXY - 1) ? MAXY - 1 : *newY + incY;
            break;
        case DIR_D:
            if(walls[*newX+1][*newY] == 1){
                return;
            };
            printf(" ");
            *newX = (*newX + incX > MAXX - 2) ? MAXX - 2 : *newX + incX;
            break;
    }
    screenGotoxy(*newX , *newY);
    printf("%c", c);
}

void movePacman(int *newX, int *newY, int d){
    moveChar(newX, newY, d, PACMAN);
}

int main() {
    static int ch = 0;
    static long timer = 0;

    keyboardInit();
    screenInit(1);
    timerInit(50);

    printChar(PACMAN, pacmanX, pacmanY);
    walls[30][5] = 1;
    printWalls();

    screenUpdate();

    while (ch != 10) // enter
    {
        // Handle user input
        if (keyhit()) {
            ch = readch();
        }

        // Update game state (move elements, verify collision, etc)
        if (timerTimeOver() == 1) {
            movePacman(&pacmanX, &pacmanY, ch);
            screenUpdate();
            timer++;
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
