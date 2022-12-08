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
    Hash *hashT;

    Vector2 screenDimensions;

    SpatialHashing(Vector2 _screenDimensions, int _amountCells);

    void RenderCells();
    void UpdateSpatialHashing(int _amountCells);
    void SearchLinesInCells(LinesManager::Line *linesTemp, int cellsCount, int amountLines);
    void SpatialHashingUpdate(LinesManager::Line *lines, Cell *cells, int cellsCount, int amountLines);

    int AmountLines(LinesManager::Line line, Cell *cells, int cellsCount, int amountLines);
    std::vector<int> CellsPassedByLine (LinesManager::Line line, Cell *cells, int cellsCount, int amountLines);


private:
    int amountCells;

    void GenerateCells();
    void DrawCells();

    bool LineLineIntersection(Vector2 firstSegmentStart, Vector2 firstSegmentEnd, Vector2 secondSegmentStart, Vector2 secondSegmentEnd);
    bool VertexInsideRectangle(Vector2 Vertex, Cell cell);
    bool CellAroundLine(Vector2 minBoudingCell, Vector2 maxBoudingCell, Vector2 minBoudingLine, Vector2 maxBoudingLine);
    std::vector<int> UsedCells(Vector2 startLine, Vector2 endLine, std::vector<int> boudingCells, Cell *cells);

};

#endif
