/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
 */

#include "keyboard.h"
#include "screen.h"
#include "timer.h"

#include "pacman.h"
#include "walls.h"
#include "dot.h"
#include "simbolo.h"



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

    screenUpdate();

    while (ch != 10) // enter
    {
        // Handle user input
        if (keyhit()) {
            ch = readch();
        }

        // Update game state (move elements, verify collision, etc)
        if (timerTimeOver() == 1) {
            movePacman(ch);
            checkDotCollision(player.x, player.y);
            checkSimboloColisoes(player.x, player.y);
            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
