#include "keyboard.h"
#include "screen.h"
#include "timer.h"
#include "logic_tautology.h"

#include "player.h"
#include "walls.h"
#include "dot.h"
#include "simbolo.h"
#include "fantasma.h"

static int ch = 0;
static int fantasmaNumero = -1;
static int gameOver = 0;

void restart(){
    centerPlayer();
    printStartingPlayer();
    ch = 0;

    initSimbolos();
    printSimbolos();
}

void gameover(){
    keyboardDestroy();
    screenDestroy();
    timerDestroy();
    gameOver = 1;
}

void morte(){
    player.lives--;
    reduzirVidas();
    if(player.lives > 0){
        restart();
    }
    else{
        gameover();
    }
}

void faseComer(){
    fantasmaNumero = checkFantasmaColisoes(player.x, player.y);
    if(fantasmaNumero != -1){
        if(is_tautology(proposicao)){
            initDots();
            Fantasmas[fantasmaNumero].active = 0;
            Fantasmas[fantasmaNumero].x = 0;
            Fantasmas[fantasmaNumero].y = 0;
        }
        else{
            morte();
        }
    }
}

int main() {
    // inits cli-lib
    keyboardInit();
    screenInit(1);
    timerInit(50);

    // inits map
    makeDefaultMap();
    printWalls();

    // inits entities
    printStartingPlayer();

    initDots();
    drawDots();

    initSimbolos();
    printSimbolos();

    // inits hud
    initPreposicao();
    initVidas();


    //test
    Fantasmas[0] = createFantasma(SCRSTARTX + 10, SCRSTARTY + 10);
    initFantasma(&Fantasmas[0]);
    initRNG();

    screenUpdate();

    while (ch != 10 && gameOver != 1) // enter
    {
        // Handle user input
        if (keyhit()) {
            ch = readch();
        }

        // Update game state (move elements, verify collision, etc)
        if (timerTimeOver() == 1) {
            drawDots();
            printSimbolos();
            movePlayer(ch);

            faseComer();

            checkDotCollision(player.x, player.y);
            checkSimboloColisoes(player.x, player.y);
            moveFantasmas();

            faseComer();

            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
