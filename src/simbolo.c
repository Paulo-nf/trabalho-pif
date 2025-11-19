#include <string.h>

#include "screen.h"
#include "logic_tautology.h"

#include "simbolo.h"

char proposicao[SIZE + 1];
int proposicaoX = SCRSTARTX, proposicaoY = SCRSTARTY+33;

typedef struct {
    int x, y;
    char c;
} Simbolo;

Simbolo simbolos[SIZE];

void initSimbolos() {
    simbolos[0].x = SCRSTARTX+42;
    simbolos[0].y = SCRSTARTY+18;
    simbolos[0].c = 'P';
    simbolos[1].x = SCRSTARTX+43;
    simbolos[1].y = SCRSTARTY+18;
    simbolos[1].c = 'v';
    simbolos[2].x = SCRSTARTX+44;
    simbolos[2].y = SCRSTARTY+18;
    simbolos[2].c = '~';
    simbolos[3].x = SCRSTARTX+45;
    simbolos[3].y = SCRSTARTY+18;
    simbolos[3].c = 'P';
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
