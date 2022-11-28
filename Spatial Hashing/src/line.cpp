#include "line.h"

LinesManager::LinesManager(){

}

void LinesManager::renderLines(){

}


void LinesManager::generateLines(int _amountLines)
{
    for(int generatedLines = 0; generatedLines < _amountLines; generatedLines ++)
    {
        line[generatedLines].startLine = Vector2(rand() % (int)this->dimensionScreen.x, rand() % (int)this->dimensionScreen.y);
        line[generatedLines].endLine = Vector2(rand() % 50 + line[generatedLines].startLine.x, rand() % 50 + line[generatedLines].startLine.y);
    }
}

void LinesManager::showLines(int _amountLines)
{
    for(int displayedLines = 0; displayedLines < _amountLines; displayedLines ++)
    {
        CV::color(0);
        CV::line(line[displayedLines].startLine, line[displayedLines].endLine, 2);
    }
}

