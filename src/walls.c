#include "walls.h"

#include "screen.h"

int walls[MAXX][MAXY] = {0};

//horizontalWall e verticalWall é só uso interno
void horizontalWall(int x1, int x2, int y){
    for(;x1 < x2; x1++){
        walls[x1][y] = 1;
    }
}

void verticalWall(int y1, int y2, int x){
    for(;y1 < y2; y1++){
        walls[x][y1] = 1;
    }
}

void makeDefaultMap(){
    horizontalWall(10, 30, 5);
    verticalWall(5, 15, 10);
}

void printWalls(){
    makeDefaultMap();
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
