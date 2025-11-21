#ifndef __SIMBOLO_H__
#define __SIMBOLO_H__

#define SIZE 8

typedef struct {
    int x, y;
    char c;
} Simbolo;

extern char proposicao[SIZE + 1];

void initSimbolos(void);
void printSimbolos(void);
void checkSimboloColisoes(int x, int y);
void initPreposicao(void);

#endif
