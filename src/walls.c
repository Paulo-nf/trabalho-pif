#include "walls.h"

#include "screen.h"

int walls[MAXX][MAXY] = {0};

void printWalls(){
    for(int i = 0; i < MAXX; i++){
        for(int j = 0; j < MAXY; j++){
            if(walls[i][j] == 1){
                screenSetColor(CYAN, BLUE);
                screenGotoxy(i, j);
                printf(" ");
            }
        }
    }
}
