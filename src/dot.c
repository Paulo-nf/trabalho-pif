/**
 * dot.c
 * Implementação para gerenciamento das pastilhas (Dots e Power Pellets).
 */

#include "dot.h"
#include "screen.h"
#include "walls.h"
#include <stdlib.h>
#include <stdio.h>

// Definição das variáveis globais declaradas como 'extern' em dot.h
Dot *all_dots = NULL;
int total_dots = 0;


static void addDot(int x, int y, DotType type) {
    total_dots++;
    all_dots = (Dot *)realloc(all_dots, total_dots * sizeof(Dot));

    if (all_dots == NULL) {
        fprintf(stderr, "Erro de alocação de memória para pastilhas!\n");
        exit(EXIT_FAILURE);
    }

    all_dots[total_dots - 1].x = x;
    all_dots[total_dots - 1].y = y;
    all_dots[total_dots - 1].type = type;
    all_dots[total_dots - 1].is_eaten = 0;
}


void initDots() {
    if (all_dots != NULL) {
        free(all_dots);
        all_dots = NULL;
        total_dots = 0;
    }

    for(int i = SCRSTARTX + 1; i < SCRENDX; i++){
        for(int j = SCRSTARTY + 1; j < SCRENDY; j++){
            

            if(walls[i][j] == 0){ 
                addDot(i, j, REGULAR_DOT); 
            }
        }
    }
    
    if (walls[SCRSTARTX + 2][SCRSTARTY + 2] == 0) {
        addDot(SCRSTARTX + 2, SCRSTARTY + 2, POWER_PELLET);
    }
}



void drawDots() {
    for (int i = 0; i < total_dots; i++) {
        if (all_dots[i].is_eaten == 0) {
            
            // Define a cor baseada no tipo de pastilha
            if (all_dots[i].type == POWER_PELLET) {
                // Desenha o Power Pellet (maior e possivelmente com cor diferente)
                screenSetColor(WHITE, DARKGRAY); 
                screenGotoxy(all_dots[i].x, all_dots[i].y);
                printf("O"); 
            } else {
                // Desenha o Ponto Regular
                screenSetColor(YELLOW, DARKGRAY);
                screenGotoxy(all_dots[i].x, all_dots[i].y);
                printf("."); 
            }
        }
    }
}


/**
 * Verifica se o Pac-Man colidiu com uma pastilha e a marca como comida.
 * @param pacmanX Coordenada X atual do Pac-Man.
 * @param pacmanY Coordenada Y atual do Pac-Man.
 */
void checkDotCollision(int pacmanX, int pacmanY) {
    for (int i = 0; i < total_dots; i++) {
        if (all_dots[i].is_eaten == 0 && 
            all_dots[i].x == pacmanX && 
            all_dots[i].y == pacmanY) {

            all_dots[i].is_eaten = 1; 
            
            // Aqui é onde a pontuação e a lógica especial (Tautologia) entrariam
            if (all_dots[i].type == POWER_PELLET) {
                // Lógica da Tautologia: Pac-Man fica invulnerável por um tempo.
                // TODO: Implementar a ativação do modo POWER.
            }
            // TODO: Adicionar a pontuação aqui.
            break; // O Pac-Man só pode comer uma pastilha por vez
        }
    }
}
