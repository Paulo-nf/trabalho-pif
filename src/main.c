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

enum direction {
    DIR_W = 119,
    DIR_A = 97,
    DIR_S = 115,
    DIR_D = 100
};

int main() {
    static int ch = 0;
    static long timer = 0;

    keyboardInit();
    screenInit(1);
    timerInit(50);

    printStartingPacman();
    makeDefaultMap();
    printWalls();

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
            screenUpdate();
            timer++;
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
