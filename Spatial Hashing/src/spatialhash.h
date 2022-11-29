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
    SpatialHashing(Vector2 _screenDimensions, int _amountCells);

    void RenderCells();
    void UpdateSpatialHashing(int _amountCells);
    //void SearchLinesInCells

private:
    struct Cell
    {
        Vector2 points[];
        Vector2 minBoundary;
        Vector2 maxBoundary;
        Vector3 color;
    };
    Cell *cell;

    int amountCells;
    Vector2 screenDimensions;

    void GenerateCells();
    void DrawCells();
};

#endif
