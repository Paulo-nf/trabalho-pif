#ifndef __FANTASMA_H__
#define __FANTASMA_H__

#define SIZE 8

typedef enum {RANDOM} AI;

enum{
    NONE, W, A, S, D
};

typedef struct {
    int x;
    int y;
    int active;
    int next_cell;
    AI ai;
} Fantasma;

extern Fantasma Fantasmas[SIZE];

void initFantasma(Fantasma *f);

void moveFantasmas(void);

Fantasma createFantasma(int x, int y);

int checkFantasmaColisoes(int pacmanX, int pacmanY);

void initRNG(void);

#endif
