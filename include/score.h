#ifndef __SCORE_H__
#define __SCORE_H__

#define SIZE 8

typedef struct {
    char name[50];
    int score;
} High_Score;

extern int score;

extern High_Score high_scores[SIZE];

void scorePoint(void);
void scoreTautology(void);
void resetScore(void);
void initHighScores(void);
void printScore(void);
void updateHighScores(int newScore, const char* playerName);

#endif
