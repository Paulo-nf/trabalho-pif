#include "walls.h"
#include "screen.h"

int walls[MAXX][MAXY] = {0};

//_horizontalWall e _verticalWall é só uso interno

void _horizontalWall(int x1, int x2, int y){
    x1 += SCRSTARTX;
    x2 += SCRSTARTX;
    y += SCRSTARTY;
    for(;x1 < x2; x1++){
        walls[x1][y] = 1;
    }
}

void _verticalWall(int y1, int y2, int x){
    y1 += SCRSTARTY;
    y2 += SCRSTARTY;
    x += SCRSTARTX;
    for(;y1 < y2; y1++){
        walls[x][y1] = 1;
    }
}

void makeDefaultMap(){
    // Outer boundary walls (the main walls of the maze)
    _horizontalWall(0, 65, 0);
    _horizontalWall(0, 65, 31);
    _verticalWall(0, 32, 0);
    _verticalWall(0, 32, 64);

    // Top section barriers
    _horizontalWall(10, 25, 5);
    _horizontalWall(40, 55, 5);

    _verticalWall(5, 10, 15);
    _verticalWall(5, 10, 50);

    // Middle section barriers
    _horizontalWall(5, 15, 12);
    _horizontalWall(20, 30, 12);
    _horizontalWall(35, 45, 12);
    _horizontalWall(50, 60, 12);

    _horizontalWall(5, 15, 19);
    _horizontalWall(20, 30, 19);
    _horizontalWall(35, 45, 19);
    _horizontalWall(50, 60, 19);

    // Bottom section barriers
    _horizontalWall(10, 25, 26);
    _horizontalWall(40, 55, 26);

    _verticalWall(22, 26, 15);
    _verticalWall(22, 26, 50);

    // Side tunnels (like Pac-Man's side warps)
    _verticalWall(14, 18, 5);
    _verticalWall(14, 18, 60);

    // Corner pockets (like power pellet areas but open)
    _horizontalWall(5, 10, 8);
    _horizontalWall(5, 10, 23);
    _horizontalWall(55, 60, 8);
    _horizontalWall(55, 60, 23);
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
