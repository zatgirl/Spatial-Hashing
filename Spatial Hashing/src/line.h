#ifndef __LINE_H__
#define __LINE_H__

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Vector2.h"
#include "spatialhash.h"

#include "gl_canvas2d.h"

class LinesManager
{
public:
    int amountLines;
    Vector2 screenDimensions;

    LinesManager(Vector2 _screenDimensions, int _amountLines);

    void RenderLines();
    void UpdateLines(int _amountLines);
    void SearchLinesInCells(SpatialHashing::Cell *cellsTemp, int cellsCount);

private:
    struct Line
    {
        Vector2 startLine;
        Vector2 endLine;
        std::vector<int> usage; ///Guarda o índice das células o segmento de linha passa
    };
    Line *line;

    void GenerateLines();
    void ShowLines();

    void LineLineIntersection();
    bool LineLineIntersection(Vector2 firstSegmentStart, Vector2 firstSegmentEnd, Vector2 secondSegmentStart, Vector2 secondSegmentEnd);
    bool VertexInsideRectangle(Vector2 Vertex, SpatialHashing::Cell cell);
    bool CellAroundLine(Vector2 minBoudingCell, Vector2 maxBoudingCell, Vector2 minBoudingLine, Vector2 maxBoudingLine);
    std::vector<int> UsedCells(Vector2 startLine, Vector2 endLine, std::vector<int> boudingCells, SpatialHashing::Cell *cell);
};

#endif
