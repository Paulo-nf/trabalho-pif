#include "walls.h"

#include "screen.h"

int walls[MAXX][MAXY] = {0};

//_horizontalWall e _verticalWall é só uso interno

void _verticalWall(int y1, int y2, int x){
    if (y1 >= y2) {
        return;
    }
    walls[x][y1] = 1;
    _verticalWall(y1 + 1, y2, x);
}


void _horizontalWall(int x1, int x2, int y){
    if (x1 >= x2) {
        return;
    }
    walls[x1][y] = 1;
    _horizontalWall(x1 + 1, x2, y);
}

void makeDefaultMap(){

    _horizontalWall(SCRSTARTX, SCRENDX + 1, SCRSTARTY);
    _horizontalWall(SCRSTARTX, SCRENDX + 1, SCRENDY);

    _verticalWall(SCRSTARTY + 1, SCRENDY, SCRSTARTX);
    _verticalWall(SCRSTARTY + 1, SCRENDY, SCRENDX);

    _horizontalWall(SCRSTARTX+16, SCRENDX - 30, SCRSTARTY+5);
}

void printWalls(){
    makeDefaultMap();
    for(int i = 0; i < MAXX; i++){
        for(int j = 0; j < MAXY; j++){
            if(walls[i][j] == WALLED){
                screenSetColor(CYAN, BLUE);
                screenGotoxy(i, j);
                printf(" ");
            }
        }
    }
}
