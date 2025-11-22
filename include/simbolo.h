#ifndef __SIMBOLO_H__
#define __SIMBOLO_H__

#define SIZE 8

typedef struct {
    int x, y;
    int active;
    char c;
} Simbolo;

extern char proposicao[SIZE + 1];

void initSimbolos(void);
void printSimbolos(void);
void checkSimboloColisoes(int x, int y);
void initProposicao(void);
void resetProposicao(void);

#endif
