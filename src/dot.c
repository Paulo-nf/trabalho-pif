#include <stdlib.h>
#include <stdio.h>

#include "screen.h"

#include "dot.h"
#include "score.h"


Dot *all_dots = NULL;
int total_dots = 0;


static void addDot(int x, int y) {
    total_dots++;
    all_dots = (Dot *)realloc(all_dots, total_dots * sizeof(Dot));

    if (all_dots == NULL) {
        fprintf(stderr, "Erro de alocação de memória para pastilhas!\n");
        exit(EXIT_FAILURE);
    }

    all_dots[total_dots - 1].x = x;
    all_dots[total_dots - 1].y = y;
    all_dots[total_dots - 1].is_eaten = 0;
}


void initDots() {
    if (all_dots != NULL) {
        free(all_dots);
        all_dots = NULL;
        total_dots = 0;
    }

    for(int i = SCRSTARTX + 1; i < SCRENDX; i++){
        for(int j = SCRSTARTY + 1; j < SCRENDY; j++){
            addDot(i, j);
        }
    }
}



void drawDots() {
    for (int i = 0; i < total_dots; i++) {
        if (all_dots[i].is_eaten == 0) {
            screenSetColor(YELLOW, DARKGRAY);
            screenGotoxy(all_dots[i].x, all_dots[i].y);
            printf(".");
        }
    }
}

void checkDotCollision(int pacmanX, int pacmanY) {
    for (int i = 0; i < total_dots; i++) {
        if (all_dots[i].is_eaten == 0 && 
            all_dots[i].x == pacmanX && 
            all_dots[i].y == pacmanY) {

            scorePoint();
            all_dots[i].is_eaten = 1; 
            break;
        }
    }
}
