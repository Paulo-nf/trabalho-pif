#include "screen.h"

#include "walls.h"
#include "player.h"

#define PACMAN_CHAR 'P'
#define MAXLIFES 3

// Definição da instância global (alocação de memória)
Pacman player = {
    .x = MINX + (MAXX - MINX) / 2, 
    .y = MINY + (MAXY - MINY) / 2,
    .inc_x = 1,
    .inc_y = 1,
    .lives = MAXLIFES
};

void initVidas(){
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(SCRSTARTX, SCRSTARTY+34);
    printf("VIDAS:");
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(SCRSTARTX + 6,SCRSTARTY+34);
    for(int i = 0; i < player.lives; i++){
        printf("S2");
    }
}

void reduzirVidas(){
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(SCRSTARTX + 6,SCRSTARTY+34);
    for(int i = 0; i < player.lives; i++){
        printf("S2");
    }
    for(int i = 0; i < MAXLIFES - player.lives; i++){
        printf("  ");
    }
}

void printStartingPlayer(){
    screenSetColor(CYAN, DARKGRAY);
    
    screenGotoxy(player.x, player.y);
    printf(" "); 
    
    screenGotoxy(player.x, player.y);
    printf("%c", PACMAN_CHAR);
}

void centerPlayer(){
    player.x = MINX + (MAXX - MINX) / 2;
    player.y = MINY + (MAXY - MINY) / 2;
}

void movePlayer(int d){
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(player.x, player.y);

    switch (d) {
        case DIR_W: 
            if(walls[player.x][player.y - 1] == 1){
                return; 
            };
            printf(" "); 
            player.y = (player.y - player.inc_y < MINY + 1) ? MINY + 1 : player.y - player.inc_y;
            break;
        case DIR_A: 
            if(walls[player.x - 1][player.y] == 1){
                return; 
            };
            printf(" "); 
            
            player.x = (player.x - player.inc_x < MINX + 1) ? MINX + 1 : player.x - player.inc_x;
            break;
        case DIR_S: 
            if(walls[player.x][player.y + 1] == 1){
                return; 
            };
            printf(" "); 
            
            player.y = (player.y + player.inc_y > MAXY - 1) ? MAXY - 1 : player.y + player.inc_y;
            break;
        case DIR_D: 
            if(walls[player.x + 1][player.y] == 1){
                return; 
            };
            printf(" "); 

            player.x = (player.x + player.inc_x > MAXX - 2) ? MAXX - 2 : player.x + player.inc_x;
            break;
    }

    screenGotoxy(player.x , player.y);
    printf("%c", PACMAN_CHAR);
}
