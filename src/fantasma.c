#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fantasma.h"
#include "walls.h"
#include "screen.h"

Fantasma Fantasmas[SIZE] = {0};

void initFantasma(Fantasma *f){
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(f->x, f->y);
    printf("T");
}

void initRNG(){
    srand(time(NULL));
}

void moveFantasma(Fantasma *f){
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
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(f->x, f->y);
    printf("T");
}

void moveFantasmas(){
    for(int i = 0; i < SIZE; i++){
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
    int tmp = 0;
    for(int i = 0; i < SIZE; i++){
        if(Fantasmas[i].active == 1){
            tmp += checkFantasmaColisao(&Fantasmas[i], pacmanX, pacmanY);
        }
    }
    return tmp;
}

Fantasma createFantasma(int x, int y) {
    Fantasma f = {
        .x = x,
        .y = y,
        .active = 1,
        .ai = RANDOM,
        .next_cell = NONE
    };
    Fantasmas[0] = f;
    return f;
}
