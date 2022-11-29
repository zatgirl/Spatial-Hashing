#include "line.h"

LinesManager::LinesManager(Vector2 _screenDimensions, int _amountLines){
    this->screenDimensions = _screenDimensions;
    this->amountLines = _amountLines;
    line = new Line[amountLines];
    LinesManager::GenerateLines();
}

void LinesManager::RenderLines(){
    LinesManager::ShowLines();
}


void LinesManager::GenerateLines()
{
    for(int generatedLines = 0; generatedLines < this->amountLines; generatedLines ++)
    {
        line[generatedLines].startLine = Vector2(rand() % (int)this->screenDimensions.x, rand() % (int)this->screenDimensions.y);
        line[generatedLines].endLine = Vector2(rand() % 50 + line[generatedLines].startLine.x, rand() % 50 + line[generatedLines].startLine.y);
    }
}

void LinesManager::ShowLines()
{
    for(int displayedLines = 0; displayedLines < this->amountLines; displayedLines ++)
    {
        CV::color(0);
        CV::line(line[displayedLines].startLine, line[displayedLines].endLine, 2);
    }
}

void LinesManager::UpdateLines(int _amountLines)
{
    this->amountLines = _amountLines;
    LinesManager::GenerateLines();
}

