#ifndef __SPATIALHASHING_H__
#define __SPATIALHASHING_H__

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Vector2.h"


class SpatialHashing
{
public:
    int amountCells;
    Vector2 screenDimensions;

    SpatialHashing(Vector2 _screenDimensions, int _amountCells);

    void GenerateCells();

private:
    struct Cell
    {
        Vector2 points[];
        Vector2 minBoundary;
        Vector2 maxBoundary;
    };
};


#endif
