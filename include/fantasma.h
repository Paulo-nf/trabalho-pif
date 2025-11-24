#ifndef __FANTASMA_H__
#define __FANTASMA_H__

#define SIZE_FANTASMAS 3
#define FANTASMA_SYMBOL "👻"

typedef enum {RANDOM, PURSUE} AI;

typedef enum {SLOW, FAST} Pace;

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
    int starting_x;
    int starting_y;
    int active;
    int next_cell;
    int timeToRespawn;
    Pace pace;
    AI ai;
} Fantasma;

extern Fantasma fantasmas[SIZE_FANTASMAS];

void initRNG(void);
void initFantasmas(void);
void initFantasma(Fantasma *f);
void moveFantasmas(void);
int checkFantasmaColisoes(int pacmanX, int pacmanY);
Fantasma createFantasma(int x, int y, AI ai, Pace pace);
void tickFantasmaRespawn(void);

#endif
