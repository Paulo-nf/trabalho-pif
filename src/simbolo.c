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
        .c = 'P'
    };

    simbolos[1] = (Simbolo){
        .x = SCRSTARTX + 43,
        .y = SCRSTARTY + 18,
        .c = 'v'
    };

    simbolos[2] = (Simbolo){
        .x = SCRSTARTX + 44,
        .y = SCRSTARTY + 18,
        .c = '~'
    };

    simbolos[3] = (Simbolo){
        .x = SCRSTARTX + 45,
        .y = SCRSTARTY + 18,
        .c = 'P'
    };
}

void initPreposicao(){
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(proposicaoX,proposicaoY);
    printf("PREPOSIÇÃO:");
    screenSetColor(WHITE, RED);
    screenGotoxy(proposicaoX + 11,proposicaoY);
    printf("        ");
}

void printSimbolo(int index){
    Simbolo *s = &simbolos[index];
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(s->x, s->y);
    printf("%c", s->c);
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
            s->x = 0;
            s->y = 0;
            strcat(proposicao, &s->c);
            screenSetColor(WHITE, is_tautology(proposicao) ? GREEN : RED);
            screenGotoxy(proposicaoX + 11,proposicaoY);
            printf("        ");
            screenGotoxy(proposicaoX + 11,proposicaoY);
            printf("%s", proposicao);
        }
    }
}
