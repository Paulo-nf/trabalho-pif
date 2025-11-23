#include <string.h>

#include "screen.h"
#include "logic_tautology.h"

#include "simbolo.h"

char proposicao[SIZE + 1];
int proposicaoX = SCRSTARTX, proposicaoY = SCRSTARTY+33;

Simbolo simbolos[SIZE];

void initSimbolos() {
    simbolos[0] = (Simbolo){
        .x = SCRSTARTX + 42,
        .y = SCRSTARTY + 18,
        .active = 1,
        .c = 'P'
    };

    simbolos[1] = (Simbolo){
        .x = SCRSTARTX + 43,
        .y = SCRSTARTY + 18,
        .active = 1,
        .c = 'v'
    };

    simbolos[2] = (Simbolo){
        .x = SCRSTARTX + 44,
        .y = SCRSTARTY + 18,
        .active = 1,
        .c = '~'
    };

    simbolos[3] = (Simbolo){
        .x = SCRSTARTX + 45,
        .y = SCRSTARTY + 18,
        .active = 1,
        .c = 'P'
    };
}

void resetSimbolos(){
    for(int i = 0; i < SIZE; i++){
        simbolos[i].active = 1;
    }
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
    for(int i = 0; i < SIZE; i++){
        printSimbolo(i);
    }
}

void checkSimboloColisoes(int x, int y){
    for(int i = 0; i < SIZE; i++){
        Simbolo *s = &simbolos[i];
        if (x == s->x && y == s->y){
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
