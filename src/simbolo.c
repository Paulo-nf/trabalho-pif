#include <string.h>

#include "screen.h"
#include "logic_tautology.h"

#include "simbolo.h"

char proposicao[SIZE_SIMBOLS + 1];
int proposicaoX = SCRSTARTX, proposicaoY = SCRSTARTY+33;

Simbolo simbolos[SIZE_SIMBOLS];

void initSimbolos() {
    simbolos[0] = (Simbolo){
        .x = SCRSTARTX + 42,
        .y = SCRSTARTY + 8,
        .active = 1,
        .c = 'P'
    };

    simbolos[1] = (Simbolo){
        .x = SCRSTARTX + 57,
        .y = SCRSTARTY + 9,
        .active = 1,
        .c = 'P'
    };

    simbolos[2] = (Simbolo){
        .x = SCRSTARTX + 4,
        .y = SCRSTARTY + 15,
        .active = 1,
        .c = 'Q'
    };

    simbolos[3] = (Simbolo){
        .x = SCRSTARTX + 59,
        .y = SCRSTARTY + 15,
        .active = 1,
        .c = 'Q'
    };

    simbolos[4] = (Simbolo){
        .x = SCRSTARTX + 13,
        .y = SCRSTARTY + 28,
        .active = 1,
        .c = 'v'
    };

    simbolos[5] = (Simbolo){
        .x = SCRSTARTX + 54,
        .y = SCRSTARTY + 28,
        .active = 1,
        .c = '^'
    };

    simbolos[6] = (Simbolo){
        .x = SCRSTARTX + 45,
        .y = SCRSTARTY + 18,
        .active = 1,
        .c = '>'
    };

    simbolos[7] = (Simbolo){
        .x = SCRSTARTX + 32,
        .y = SCRSTARTY + 3,
        .active = 1,
        .c = '='
    };

    simbolos[8] = (Simbolo){
        .x = SCRSTARTX + 8,
        .y = SCRSTARTY + 21,
        .active = 1,
        .c = '~'
    };
}

void initProposicao(){
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(proposicaoX,proposicaoY);
    printf("PREPOSIÇÃO:");
    screenSetColor(WHITE, RED);
    screenGotoxy(proposicaoX + 11,proposicaoY);
    printf("        ");
}

void resetProposicao(){
    proposicao[0] = '\0';
    screenSetColor(WHITE,RED);
    screenGotoxy(proposicaoX + 11,proposicaoY);
    printf("        ");
    screenGotoxy(proposicaoX + 11,proposicaoY);
    printf("%s", proposicao);
}

void printSimbolo(int index){
    Simbolo *s = &simbolos[index];
    if(s->active == 1){
        screenSetColor(WHITE, DARKGRAY);
        screenGotoxy(s->x, s->y);
        printf("%c", s->c);
    }
}

void printSimbolos(){
    for(int i = 0; i < SIZE_SIMBOLS; i++){
        printSimbolo(i);
    }
}

void simboloRespawn(int i){
    simbolos[i].timeToRespawn = 0;
    simbolos[i].active = 1;
}

void tickSimboloRespawn(){
    for(int i = 0; i < SIZE_SIMBOLS; i++){
        if(simbolos[i].active == 0){
            simbolos[i].timeToRespawn++;
            if(simbolos[i].timeToRespawn == 800){
                simboloRespawn(i);
            }
        }
    }
}

void checkSimboloColisoes(int x, int y){
    for(int i = 0; i < SIZE_SIMBOLS; i++){
        Simbolo *s = &simbolos[i];
        if (x == s->x && y == s->y && s->active == 1){
            strcat(proposicao, &s->c);
            simbolos[i].active = 0;
            screenSetColor(WHITE, is_tautology(proposicao) ? GREEN : RED);
            screenGotoxy(proposicaoX + 11,proposicaoY);
            printf("        ");
            screenGotoxy(proposicaoX + 11,proposicaoY);
            printf("%s", proposicao);
        }
    }
}
