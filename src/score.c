#include <string.h>

#include "score.h"
#include "screen.h"

int score = -10;

High_Score high_scores[SIZE] = {0};

void initHighScores(){
    FILE *fptr;
    fptr = fopen("scores.txt", "r");
    for(int i = 0; i < SIZE; i++){
        char name[50];
        int score;

        fscanf(fptr, " %49s", name);
        fscanf(fptr, "%d", &score);

        strcpy(high_scores[i].name, name);
        high_scores[i].score = score;
    }
    fclose(fptr);
}

void scorePoint(){
    score += 10;
}

void scoreTautology(){
    score += 1000;
}

void resetScore(){
    score = -10;
}

void printScore(){
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(SCRSTARTX, SCRSTARTY+35);
    printf("%06d", score);
}
