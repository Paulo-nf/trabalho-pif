#ifndef __PLAYER_H__
#define __PLAYER_H__

#define PACMAN_SYMBOL "😛"
#define MAXLIFES 3

enum direction {
    STILL = 0,
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
    int direction;
    int score;
} Pacman;


// Declaração da instância global do Pac-Man (extern)
extern Pacman player;

void printPlayer(void);
void centerPlayer(void);
void changePlayerDirection(int d);
void movePlayer(void);
void initVidasHUD(void);
void resetVidas(void);
void reduzirVidas(void);

#endif
