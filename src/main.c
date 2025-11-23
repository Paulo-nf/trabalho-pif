#include <string.h>

#include "keyboard.h"
#include "screen.h"
#include "timer.h"
#include "logic_tautology.h"

#include "player.h"
#include "walls.h"
#include "dot.h"
#include "simbolo.h"
#include "fantasma.h"
#include "menu.h"
#include "score.h"

#define IS_WASD(c) (strchr("wasdWASD", (c)) != NULL)

/*TODO:
 * mapa/walls
 * simbolos
 * AI perseguir
 * trocar por power up temporario?
 * limpar dot.c/h
 * colocar scores certinho
*/

static int ch = 0;
static int fantasmaQueColide = -1;
static int gameOver = 0;

void restart(){
    centerPlayer();
    printPlayer();
    ch = 0;

    resetProposicao();
    initSimbolos();
    printSimbolos();
}

void gameover(){
    gameOver = 1;
    if(score > high_scores[SIZE - 1].score){
        keyboardDestroy();
        screenSetColor(YELLOW, DARKGRAY);
        screenInit(1);
        char playerName[50];
        getPlayerName(playerName, sizeof(playerName));
        while (getchar() != '\n');
        keyboardInit();
        updateHighScores(score, playerName);
    }
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

void comer(){
    scoreTautology();
    initDots();
    checkDotCollision(player.x, player.y);
    printPlayer();
    printSimbolos();
    Fantasmas[fantasmaQueColide].active = 0;
    Fantasmas[fantasmaQueColide].x = 0;
    Fantasmas[fantasmaQueColide].y = 0;
}

void comerOuMorrer(){
    fantasmaQueColide = checkFantasmaColisoes(player.x, player.y);
    if(fantasmaQueColide != -1){
        if(is_tautology(proposicao)){
            comer();
        }
        else{
            morte();
        }
        resetSimbolos();
        resetProposicao();
    }
}

int main() {

    // inits cli-lib
    keyboardInit();
    screenInit(1);
    timerInit(50);

    initHighScores();
    initRNG();

    while(1){
        menu();

        ch = getchar();

        if(ch == 10){ // enter

            // inits map
            makeDefaultMap();
            printWalls();

            // inits entities
            centerPlayer();
            resetVidas();
            printPlayer();

            initDots();
            drawDots();

            initFantasmas();

            initSimbolos();
            resetProposicao();
            printSimbolos();

            // inits hud
            initProposicao();
            initVidasHUD();

            resetScore();

            screenUpdate();

            gameOver = 0;

            while ((ch != 81 && ch != 113) && gameOver != 1) // q e Q
            {
                // Handle user input
                if (keyhit()) {
                    ch = readch();
                }

                // Update game state (move elements, verify collision, etc)
                if (timerTimeOver() == 1) {
                    tickRespawn();

                    drawDots();
                    printSimbolos();

                    if (IS_WASD(ch)) {
                        changePlayerDirection(ch);
                    }
                    movePlayer();

                    comerOuMorrer();

                    checkDotCollision(player.x, player.y);
                    checkSimboloColisoes(player.x, player.y);
                    moveFantasmas();

                    comerOuMorrer();
                    printScore();
                    printWalls();

                    screenUpdate();
                }
            }
            ch = 0;
        }
        if(ch == 81 || ch == 113){ // q e
            saveHighScores();
            freeHighScores();

            keyboardDestroy();
            screenDestroy();
            timerDestroy();

            return 0;
        }
    }


}

