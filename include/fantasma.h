#ifndef __FANTASMA_H__
#define __FANTASMA_H__

#define SIZE 8
#define FANTASMA_SYMBOL "👻"

typedef enum {RANDOM} AI;

enum{
    NONE,
    W,
    A,
    S,
    D
};

typedef struct {
    int x;
    int y;
    int active;
    int next_cell;
    AI ai;
} Fantasma;

extern Fantasma Fantasmas[SIZE];

void initRNG(void);
void initFantasma(Fantasma *f);
void moveFantasmas(void);
int checkFantasmaColisoes(int pacmanX, int pacmanY);
Fantasma createFantasma(int x, int y);

#endif
