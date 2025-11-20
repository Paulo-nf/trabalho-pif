#ifndef __PACMAN_H__
#define __PACMAN_H__

enum direction {
    DIR_W = 119,
    DIR_A = 97,
    DIR_S = 115,
    DIR_D = 100
};

typedef struct {
    int x;
    int y;
    int inc_x;
    int inc_y;
    int lives;
    int score;
} Pacman;


// Declaração da instância global do Pac-Man (extern)
extern Pacman player;

void printStartingPacman(void);
// A função movePacman agora receberá a direção e a struct por referência
void movePacman(int d); 

#endif
