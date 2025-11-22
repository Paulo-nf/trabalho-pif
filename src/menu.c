#include <stdio.h>

#include "screen.h"

#include "menu.h"
#include "player.h"
#include "fantasma.h"

static int line = 0;

void newLine(){
    screenGotoxy(SCRSTARTX,SCRSTARTY + line);
    line++;
}

void spaceOut(int x){
    line += x;
}

void menu(){
    screenSetColor(YELLOW, DARKGRAY);
    screenInit(1);
    screenSetColor(WHITE, DARKGRAY);
    newLine();
    printf("Uma estoria muitu linda:");

    newLine();
    printf("c:");

    spaceOut(10);

    newLine();
    screenSetColor(GREEN, DARKGRAY);
    printf(PACMAN_SYMBOL);
    screenSetColor(WHITE, DARKGRAY);
    printf(" <- Você");

    newLine();
    screenSetColor(GREEN, DARKGRAY);
    printf("P");
    screenSetColor(WHITE, DARKGRAY);
    printf(" <- Proposições e simbolos logicos");

    newLine();
    screenSetColor(CYAN, DARKGRAY);
    printf(FANTASMA_SYMBOL);
    screenSetColor(WHITE, DARKGRAY);
    printf(" <- Fantasma da tautologia, faça uma tautologia pra comer ele!");

    spaceOut(1);
    newLine();
    printf("Aperter ENTER para começar");

    screenUpdate();
    line = 0;
}
