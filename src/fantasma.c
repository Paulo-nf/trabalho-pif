#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "screen.h"

#include "fantasma.h"
#include "walls.h"
#include "player.h"

static int pacer = 0;

Fantasma fantasmas[SIZE_FANTASMAS] = {0};

void initFantasma(Fantasma *f){
    screenSetColor(GREEN, DARKGRAY);
    screenGotoxy(f->x, f->y);
    printf(FANTASMA_SYMBOL);
}

void initFantasmas(){
    fantasmas[0] = createFantasma(SCRSTARTX + 1, SCRENDY - 1, RANDOM, FAST);
    initFantasma(&fantasmas[0]);
    fantasmas[1] = createFantasma(SCRENDX - 2, SCRENDY - 1, RANDOM, FAST);
    initFantasma(&fantasmas[1]);
    fantasmas[2] = createFantasma((SCRSTARTX + SCRENDX)/2, SCRSTARTY+1, PURSUE, SLOW);
    initFantasma(&fantasmas[2]);
}

void fantasmaRespawn(int i){
    fantasmas[i].timeToRespawn = 0;
    fantasmas[i].active = 1;
    fantasmas[i].x =  fantasmas[i].starting_x;
    fantasmas[i].y =  fantasmas[i].starting_y;
    fantasmas[i].next_cell = NONE;
}

void tickFantasmaRespawn(){
    for(int i = 0; i < SIZE_FANTASMAS; i++){
        if(fantasmas[i].active == 0){
            fantasmas[i].timeToRespawn++;
            if(fantasmas[i].timeToRespawn == 200){
                fantasmaRespawn(i);
            }
        }
    }
}

void initRNG(){
    srand(time(NULL));
}

void moveFantasma(Fantasma *f, int target_x, int target_y){
    screenSetColor(GREEN, DARKGRAY);
    screenGotoxy(f->x, f->y);
    printf(" ");

    if(f->ai == RANDOM) {
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
    } else {
        int dx = target_x - f->x;
        int dy = target_y - f->y;

        int best_dir = NONE;
        int best_score = -1000; // Very low initial score

        if(walls[f->x][f->y - 1] == OPEN) {
            int new_dx = target_x - f->x;
            int new_dy = target_y - (f->y - 1);
            int score = (abs(dx) - abs(new_dx)) + (abs(dy) - abs(new_dy));
            if(score > best_score) {
                best_score = score;
                best_dir = W;
            }
        }

        if(walls[f->x - 1][f->y] == OPEN) {
            int new_dx = target_x - (f->x - 1);
            int new_dy = target_y - f->y;
            int score = (abs(dx) - abs(new_dx)) + (abs(dy) - abs(new_dy));
            if(score > best_score) {
                best_score = score;
                best_dir = A;
            }
        }

        if(walls[f->x][f->y + 1] == OPEN) {
            int new_dx = target_x - f->x;
            int new_dy = target_y - (f->y + 1);
            int score = (abs(dx) - abs(new_dx)) + (abs(dy) - abs(new_dy));
            if(score > best_score) {
                best_score = score;
                best_dir = S;
            }
        }

        if(walls[f->x + 1][f->y] == OPEN) {
            int new_dx = target_x - (f->x + 1);
            int new_dy = target_y - f->y;
            int score = (abs(dx) - abs(new_dx)) + (abs(dy) - abs(new_dy));
            if(score > best_score) {
                best_score = score;
                best_dir = D;
            }
        }

        if(best_dir == NONE) {
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
        } else {
            f->next_cell = best_dir;
        }
    }
    if(pacer % 3 != 0){
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
    }

    screenGotoxy(f->x, f->y);
    printf(FANTASMA_SYMBOL);
}

void moveFantasmas(){
    pacer++;
    for(int i = 0; i < SIZE_FANTASMAS; i++){
        if(fantasmas[i].active == 1){
            moveFantasma(&fantasmas[i], player.x, player.y);
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
        if(fantasmas[i].active == 1){
            if(checkFantasmaColisao(&fantasmas[i], pacmanX, pacmanY) == 1){
            return i;
            }
        }
    }
    return -1;
}

Fantasma createFantasma(int x, int y, AI ai, Pace pace) {
    Fantasma f = {
        .x = x,
        .y = y,
        .starting_x = x,
        .starting_y = y,
        .active = 1,
        .ai = ai,
        .pace = pace,
        .next_cell = NONE
    };
    return f;
}
