#ifndef __LINE_H__
#define __LINE_H__

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Vector2.h"

#include "gl_canvas2d.h"
#define DEF_MAX_CELLS_PASSED_BY_LINES 100

class LinesManager
{
public:
    struct Line
    {
        Vector2 startLine;
        Vector2 endLine;
        int CellsPassedByLine[DEF_MAX_CELLS_PASSED_BY_LINES]; ///Guarda o índice das células o segmento de linha passa
        int AmountCellsPassed;
    };
    Line *lines;

    int amountLines;
    Vector2 screenDimensions;

    LinesManager(Vector2 _screenDimensions, int _amountLines);

    void RenderLines();
    void UpdateLines(int _amountLines);
    void GenerateLines();

private:


    void ShowLines();

    void LineLineIntersection();

};

#endif
