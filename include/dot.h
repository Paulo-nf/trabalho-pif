/**
 * dot.h
 * Estrutura para gerenciar as pastilhas e power pellets no jogo.
*/

#ifndef __DOT_H__
#define __DOT_H__


typedef enum {
    REGULAR_DOT = 2, 
    POWER_PELLET = 3,   
    CONTRADICTORY_DOT = 4 
} DotType;


typedef struct {
    int x;
    int y;
    DotType type;
    int is_eaten;
} Dot;

//Ponteiro para o array dinâmico de pastilhas
//Váriavel global externa declarada em dot.c
extern Dot *all_dots;
extern int total_dots;

void initDots(void);
void drawDots(void);
void checkDotCollision(int pacmanX, int pacmanY);

#endif
