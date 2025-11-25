#ifndef __DOT_H__
#define __DOT_H__

typedef struct {
    int x;
    int y;
    int is_eaten;
} Dot;


extern Dot *all_dots;
extern int total_dots;

void initDots(void);
void drawDots(void);
void checkDotCollision(int pacmanX, int pacmanY);

#endif
