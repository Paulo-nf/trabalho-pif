#ifndef __SIMBOLO_H__
#define __SIMBOLO_H__

#define SIZE_SIMBOLS 9

typedef struct {
    int x, y;
    int active;
    int timeToRespawn;
    char c;
} Simbolo;

extern char proposicao[SIZE_SIMBOLS + 1];

void initSimbolos(void);
void printSimbolos(void);
void checkSimboloColisoes(int x, int y);
void initProposicao(void);
void resetProposicao(void);
void tickSimboloRespawn();

#endif
