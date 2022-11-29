#ifndef __SPATIALHASHING_H__
#define __SPATIALHASHING_H__

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Vector2.h"
#include "vector3.h"

#include "gl_canvas2d.h"

class SpatialHashing
{
public:
    int amountCells;
    Vector2 screenDimensions;

    SpatialHashing(Vector2 _screenDimensions, int _amountCells);

    void RenderCells();

    void GenerateCells();

    void DrawCells();

private:
    struct Cell
    {
        Vector2 points[];
        Vector2 minBoundary;
        Vector2 maxBoundary;
        Vector3 color;
    };
    Cell *cell;
};


#endif
