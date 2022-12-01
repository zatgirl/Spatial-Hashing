#ifndef __SPATIALHASHING_H__
#define __SPATIALHASHING_H__

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Vector2.h"
#include "vector3.h"

#include "line.h"
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

    struct Hash
    {
        int usage[MAXCELLS], initialIndex[MAXCELLS], finalIndex[MAXCELLS];
        int hashTable[SIZE_HASH];
    };
    Hash *hashh;

    Vector2 screenDimensions;

    SpatialHashing(Vector2 _screenDimensions, int _amountCells);

    void RenderCells();
    void UpdateSpatialHashing(int _amountCells);
    void SearchLinesInCells(LinesManager::Line *linesTemp, int cellsCount);
    void FeedHash();

private:
    int amountCells;


    void GenerateCells();
    void DrawCells();

    bool LineLineIntersection(Vector2 firstSegmentStart, Vector2 firstSegmentEnd, Vector2 secondSegmentStart, Vector2 secondSegmentEnd);
    bool VertexInsideRectangle(Vector2 Vertex, LinesManager::Line line);
    bool CellAroundLine(Vector2 minBoudingCell, Vector2 maxBoudingCell, Vector2 minBoudingLine, Vector2 maxBoudingLine);
    std::vector<int> UsedCells(Vector2 startLine, Vector2 endLine, std::vector<int> boudingCells, LinesManager::Line *lines);

};

#endif
