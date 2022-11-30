#ifndef __SPATIALHASHING_H__
#define __SPATIALHASHING_H__

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Vector2.h"
#include "vector3.h"

#include "gl_canvas2d.h"

#define MAXCELLS 50
#define SIZE_HASH 1000000

class SpatialHashing
{
public:
    struct Cell
    {
        Vector2 points[];
        Vector2 minBoundary;
        Vector2 maxBoundary;
        Vector3 color;
    };
    Cell *cells;

    struct Hash{
        int usage[MAXCELLS], initialIndex[MAXCELLS], finalIndex[MAXCELLS];
        int hashTable[SIZE_HASH];
    };
    Hash *hashh;

    SpatialHashing(Vector2 _screenDimensions, int _amountCells);

    void RenderCells();
    void UpdateSpatialHashing(int _amountCells);

private:
    int amountCells;
    Vector2 screenDimensions;

    void GenerateCells();
    void DrawCells();
};

#endif
