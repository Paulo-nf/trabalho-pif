#include <stdio.h>

#include "screen.h"

#include "menu.h"
#include "player.h"
#include "fantasma.h"
#include "score.h"

static int line = 0;

void newLine(){
    screenGotoxy(SCRSTARTX,SCRSTARTY + line);
    line++;
}

void spaceOut(int x){
    line += x;
}

void printHighScores(int i){
    if(high_scores[i].score == 0){
        return;
    }
    newLine();
    printf("%s: %d", high_scores[i].name, high_scores[i].score);
    printHighScores(i+1);
}

void menu(){
    screenSetColor(YELLOW, DARKGRAY);
    screenInit(1);
    screenSetColor(WHITE, DARKGRAY);
    newLine();
    printf("Pacman, confuso com a frase 'só sei que nada sei', parou diante");
    newLine();
    printf("de um fantasma e refletiu.");
    newLine();
    printf("'Se eu duvido que existo, ainda preciso existir para ter");
    newLine();
    printf("a dúvida', pensou.");
    newLine();
    printf("Ele percebeu que algumas coisas são verdadeiras por si só,");
    newLine();
    printf("como 'o labirinto é azul ou não é azul'.");
    newLine();
    newLine();
    printf("Ajuda Pacman a fazer tautologias e superar seu desânimo!");

    spaceOut(7);

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

    spaceOut(1);
    newLine();
    printf("HIGH SCORES:");
    printHighScores(0);

    screenUpdate();
    line = 0;
}
