#ifndef __SPATIALHASHING_H__
#define __SPATIALHASHING_H__

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Vector2.h"


class SpatialHashing
{
public:
    int _amountCells;
    void generateCells(int width, int height);

private:
    struct Cell
    {
        Vector2 points[];
        Vector2 minBoundary;
        Vector2 maxBoundary;
    };
};


#endif
