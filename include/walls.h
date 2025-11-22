#ifndef __WALLS_H__
#define __WALLS_H__

#include "screen.h"

extern int walls[MAXX][MAXY];

enum{
    OPEN = 0,
    WALLED = 1
};

void makeDefaultMap(void);
void printWalls(void);

#endif
