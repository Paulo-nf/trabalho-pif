/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
 */

#include "keyboard.h"
#include "logic_tautology.h"
#include "screen.h"
#include "timer.h"

#include "pacman.h"
#include "walls.h"
#include "dot.h"
#include "simbolo.h"
#include "fantasma.h"



int main() {
    static int ch = 0;

    // inits cli-lib
    keyboardInit();
    screenInit(1);
    timerInit(50);

    // inits map
    makeDefaultMap();
    printWalls();


    // inits entities
    printStartingPacman();

    initDots();
    drawDots();

    initSimbolos();
    printSimbolos();

    // inits hud
    initPreposicao();


    //test
    Fantasmas[0] = createFantasma(SCRSTARTX + 10, SCRSTARTY + 10);
    initFantasma(&Fantasmas[0]);
    initRNG();

    screenUpdate();

    while (ch != 10) // enter
    {
        // Handle user input
        if (keyhit()) {
            ch = readch();
        }

        // Update game state (move elements, verify collision, etc)
        if (timerTimeOver() == 1) {
            drawDots();
            printSimbolos();
            movePacman(ch);

            if(checkFantasmaColisoes(player.x, player.y) != 0){
                if(is_tautology(proposicao)){
                    Fantasmas[0].active = 0;
                    Fantasmas[0].x = 0;
                    Fantasmas[0].y = 0;
                }
                else{
                keyboardDestroy();
                screenDestroy();
                timerDestroy();
                return 0;
                }
            }

            checkDotCollision(player.x, player.y);
            checkSimboloColisoes(player.x, player.y);
            moveFantasmas();

            if(checkFantasmaColisoes(player.x, player.y) != 0){
                if(is_tautology(proposicao)){
                    Fantasmas[0].active = 0;
                    Fantasmas[0].x = 0;
                    Fantasmas[0].y = 0;
                }
                else{
                    keyboardDestroy();
                    screenDestroy();
                    timerDestroy();
                    return 0;
                }
            }



            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
