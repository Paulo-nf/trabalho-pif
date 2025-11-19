#include "walls.h"

#include "screen.h"

int walls[MAXX][MAXY] = {0};

//_horizontalWall e _verticalWall é só uso interno
void _horizontalWall(int x1, int x2, int y){
    for(;x1 < x2; x1++){
        walls[x1][y] = WALLED;
    }
}

void _verticalWall(int y1, int y2, int x){
    for(;y1 < y2; y1++){
        walls[x][y1] = WALLED;
    }
}

void makeDefaultMap(){
    
    _horizontalWall(SCRSTARTX, SCRENDX + 1, SCRSTARTY); 
    _horizontalWall(SCRSTARTX, SCRENDX + 1, SCRENDY);
    
    _verticalWall(SCRSTARTY + 1, SCRENDY, SCRSTARTX);
    _verticalWall(SCRSTARTY + 1, SCRENDY, SCRENDX);
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
