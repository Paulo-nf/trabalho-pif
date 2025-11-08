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
    printf(" ");
    switch (d) {
        case DIR_W:
            *newY = (*newY - incY < MINY + 1) ? MINY + 1 : *newY - incY;
            break;
        case DIR_A:
            *newX = (*newX - incX < MINX + 1) ? MINX + 1 : *newX - incX;
            break;
        case DIR_S:
            *newY = (*newY + incY > MAXY - 1) ? MAXY - 1 : *newY + incY;
            break;
        case DIR_D:
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
