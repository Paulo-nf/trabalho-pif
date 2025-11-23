#include <string.h>
#include <stdlib.h>

#include "score.h"
#include "screen.h"

int score = -10;
High_Score *high_scores;
int high_scores_size = 0;

void getPlayerName(char *nameBuffer, int bufferSize) {
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(SCRSTARTX, SCRSTARTY+20);
    printf("Enter your name: ");

    // Simple input - you might want to implement proper input handling
    if (scanf("%49s", nameBuffer) != 1) {
        strcpy(nameBuffer, "Player");
    }
}

void initHighScores(){
    high_scores = (High_Score*)calloc(SIZE, sizeof(High_Score));
    if (high_scores == NULL) {
        return;
    }
    high_scores_size = SIZE;

    // Try to load from file
    FILE *fptr = fopen("scores.txt", "r");
    if (fptr == NULL) {
        return;
    }

    for(int i = 0; i < SIZE; i++){
        char name[50];
        int score;

        if (fscanf(fptr, " %49s", name) == 1 && fscanf(fptr, "%d", &score) == 1) {
            strcpy(high_scores[i].name, name);
            high_scores[i].score = score;
        }
    }
    fclose(fptr);
}

void updateHighScores(int newScore, const char* playerName) {
    int insert_index;

    for (int i = 0; i < high_scores_size; i++) {
        if (newScore > high_scores[i].score) {
            insert_index = i;
            break;
        }
    }

    for (int i = high_scores_size - 1; i > insert_index; i--) {
        strcpy(high_scores[i].name, high_scores[i-1].name);
        high_scores[i].score = high_scores[i-1].score;
    }

    strcpy(high_scores[insert_index].name, playerName);
    high_scores[insert_index].score = newScore;
}

void saveHighScores(){
    if (high_scores == NULL) {
        return;
    }

    FILE *fptr = fopen("scores.txt", "w");
    if (fptr == NULL) {
        return;
    }

    for (int i = 0; i < high_scores_size; i++) {
        fprintf(fptr, "%s %d\n", high_scores[i].name, high_scores[i].score);
    }
    fclose(fptr);
}

void freeHighScores(void) {
    if (high_scores != NULL) {
        free(high_scores);
        high_scores = NULL;
        high_scores_size = 0;
    }
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
