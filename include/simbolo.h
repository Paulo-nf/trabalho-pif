#ifndef __SIMBOLO_H__
#define __SIMBOLO_H__

#define SIZE 8

void initSimbolos(void);

void printSimbolo(int);

void printSimbolos(void);

void checkSimboloColisoes(int x, int y);

void initPreposicao(void);

extern char proposicao[SIZE + 1];

#endif
