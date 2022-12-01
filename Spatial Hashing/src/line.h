#ifndef __LINE_H__
#define __LINE_H__

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Vector2.h"

#include "gl_canvas2d.h"

class LinesManager
{
public:
    struct Line
    {
        Vector2 startLine;
        Vector2 endLine;
        std::vector<int> CellsPassedByLine; ///Guarda o �ndice das c�lulas o segmento de linha passa
    };
    Line *lines;

    int amountLines;
    Vector2 screenDimensions;

    LinesManager(Vector2 _screenDimensions, int _amountLines);

    void RenderLines();
    void UpdateLines(int _amountLines);


private:

    void GenerateLines();
    void ShowLines();

    void LineLineIntersection();

};

#endif
