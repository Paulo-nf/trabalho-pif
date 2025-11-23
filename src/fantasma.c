#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "screen.h"

#include "fantasma.h"
#include "walls.h"

Fantasma Fantasmas[SIZE_FANTASMAS] = {0};

void initFantasma(Fantasma *f){
    screenSetColor(GREEN, DARKGRAY);
    screenGotoxy(f->x, f->y);
    printf(FANTASMA_SYMBOL);
}

void initFantasmas(){
    Fantasmas[0] = createFantasma(SCRSTARTX + 1, SCRENDY - 1);
    initFantasma(&Fantasmas[0]);
    Fantasmas[1] = createFantasma(SCRENDX - 2, SCRENDY - 1);
    initFantasma(&Fantasmas[1]);
    Fantasmas[2] = createFantasma((SCRSTARTX + SCRENDX)/2, SCRSTARTY+1);
    initFantasma(&Fantasmas[2]);
}

void fantasmaRespawn(int i){
    Fantasmas[i].timeToRespawn = 0;
    Fantasmas[i].active = 1;
    Fantasmas[i].x =  Fantasmas[i].starting_x;
    Fantasmas[i].y =  Fantasmas[i].starting_y;
    Fantasmas[i].next_cell = NONE;
}

void tickRespawn(){
    for(int i = 0; i < SIZE_FANTASMAS; i++){
        if(Fantasmas[i].active == 0){
            Fantasmas[i].timeToRespawn++;
            if(Fantasmas[i].timeToRespawn == 200){
                fantasmaRespawn(i);
            }
        }
    }
}

void initRNG(){
    srand(time(NULL));
}

void moveFantasma(Fantasma *f){
    screenSetColor(GREEN, DARKGRAY);
    screenGotoxy(f->x, f->y);
    printf(" ");

    if(f->next_cell == NONE){
        int random_number;
        int flag = 0;
        do {
            random_number = rand() % 4;

            switch(random_number) {
                case 0:
                    if(walls[f->x][f->y - 1] == OPEN) {
                        f->next_cell = W;
                        flag = 1;
                    }
                    break;
                case 1:
                    if(walls[f->x - 1][f->y] == OPEN) {
                        f->next_cell = A;
                        flag = 1;
                    }
                    break;
                case 2:
                    if(walls[f->x][f->y + 1] == OPEN) {
                        f->next_cell = S;
                        flag = 1;
                    }
                    break;
                case 3:
                    if(walls[f->x + 1][f->y] == OPEN) {
                        f->next_cell = D;
                        flag = 1;
                    }
                    break;
            }
        } while(flag == 0);
    }

    switch(f->next_cell) {
        case W:
            f->y--;
            if(walls[f->x][f->y - 1] == WALLED) {
                f->next_cell = NONE;
            }
            break;
        case A:
            f->x--;
            if(walls[f->x - 1][f->y] == WALLED) {
                f->next_cell = NONE;
            }
            break;
        case S:
            f->y++;
            if(walls[f->x][f->y + 1] == WALLED) {
                f->next_cell = NONE;
            }
            break;
        case D:
            f->x++;
            if(walls[f->x + 1][f->y] == WALLED) {
                f->next_cell = NONE;
            }
            break;
    }
    screenGotoxy(f->x, f->y);
    printf(FANTASMA_SYMBOL);
}

void moveFantasmas(){
    for(int i = 0; i < SIZE_FANTASMAS; i++){
        if(Fantasmas[i].active == 1){
            moveFantasma(&Fantasmas[i]);
        }
    }
}

int checkFantasmaColisao(Fantasma *f, int pacmanX, int pacmanY){
    if(pacmanX == f->x && pacmanY == f->y){
        return 1;
    }
    return 0;
}

int checkFantasmaColisoes(int pacmanX, int pacmanY){
    for(int i = 0; i < SIZE_FANTASMAS; i++){
        if(Fantasmas[i].active == 1){
            if(checkFantasmaColisao(&Fantasmas[i], pacmanX, pacmanY) == 1){
            return i;
            }
        }
    }
    return -1;
}

Fantasma createFantasma(int x, int y) {
    Fantasma f = {
        .x = x,
        .y = y,
        .starting_x = x,
        .starting_y = y,
        .active = 1,
        .ai = RANDOM,
        .next_cell = NONE
    };
    return f;
}
