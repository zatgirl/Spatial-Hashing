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
    };
    Line line[];

    Vector2 dimensionScreen;

    LinesManager();

    void renderLines();

    void generateLines(int _amountLines);

    void showLines(int _amountLines);

};


#endif
