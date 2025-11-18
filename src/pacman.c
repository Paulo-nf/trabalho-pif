#include "screen.h"
#include "walls.h"
#include "pacman.h"

#define PACMAN_CHAR 'P'

// Definição da instância global (alocação de memória)
Pacman player = {
    .x = MINX + (MAXX - MINX) / 2, 
    .y = MINY + (MAXY - MINY) / 2,
    .inc_x = 1,
    .inc_y = 1,
    .lives = 3 
};

void printStartingPacman(){
    screenSetColor(CYAN, DARKGRAY);
    
    screenGotoxy(player.x, player.y);
    printf(" "); 
    
    screenGotoxy(player.x, player.y);
    printf("%c", PACMAN_CHAR);
}

void movePacman(int d){
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