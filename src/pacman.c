#include "screen.h"
#include "walls.h"

#define PACMAN 'P'

int pacmanX = 34, pacmanY = 12;
int incX = 1, incY = 1;

enum direction {
    DIR_W = 119,
    DIR_A = 97,
    DIR_S = 115,
    DIR_D = 100
};

void printStartingPacman(){
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(pacmanX, pacmanY);
    printf(" ");
    screenGotoxy(pacmanX, pacmanY);
    printf("%c", PACMAN);
}

void movePacman(int d){
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(pacmanX, pacmanY);
    switch (d) {
        case DIR_W:
            if(walls[pacmanX][pacmanY-1] == 1){
                return;
            };
            printf(" ");
            pacmanY = (pacmanY - incY < MINY + 1) ? MINY + 1 : pacmanY - incY;
            break;
        case DIR_A:
            if(walls[pacmanX-1][pacmanY] == 1){
                return;
            };
            printf(" ");
            pacmanX = (pacmanX - incX < MINX + 1) ? MINX + 1 : pacmanX - incX;
            break;
        case DIR_S:
            if(walls[pacmanX][pacmanY+1] == 1){
                return;
            };
            printf(" ");
            pacmanY = (pacmanY + incY > MAXY - 1) ? MAXY - 1 : pacmanY + incY;
            break;
        case DIR_D:
            if(walls[pacmanX+1][pacmanY] == 1){
                return;
            };
            printf(" ");
            pacmanX = (pacmanX + incX > MAXX - 2) ? MAXX - 2 : pacmanX + incX;
            break;
    }
    screenGotoxy(pacmanX , pacmanY);
    printf("%c", PACMAN);
}
