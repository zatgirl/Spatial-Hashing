#include "line.h"

LinesManager::LinesManager(Vector2 _screenDimensions, int _amountLines)
{
    this->screenDimensions = _screenDimensions;
    this->amountLines = _amountLines;
    lines = new Line[_amountLines];

    LinesManager::GenerateLines();
}

void LinesManager::RenderLines()
{
    LinesManager::ShowLines();
}

void LinesManager::UpdateLines(int _amountLines)
{
    this->amountLines = _amountLines;
    lines = new Line[_amountLines];
    LinesManager::GenerateLines();
}

///Voltar e arrumar, gerando apenas retas de 0° a 90°
void LinesManager::GenerateLines()
{
    for(int generatedLines = 0; generatedLines < this->amountLines; generatedLines ++)
    {
        float startX, startY, endX, endY;
        startX = rand() % (int)this->screenDimensions.x;
        startY = rand() % (int)this->screenDimensions.y;
        lines[generatedLines].startLine = Vector2(startX, startY);

        endX = rand() % 200 + lines[generatedLines].startLine.x;
        endX = (endX > (int)this->screenDimensions.x) ? (int)this->screenDimensions.x : endX;

        endY = rand() % 200 + lines[generatedLines].startLine.y;
        endY = (endY > (int)this->screenDimensions.y) ? (int)this->screenDimensions.y : endY;
        lines[generatedLines].endLine = Vector2(endX, endY);
    }
}

void LinesManager::ShowLines()
{
    for(int displayedLines = 0; displayedLines < this->amountLines; displayedLines ++)
    {
        CV::color(0);
        CV::line(lines[displayedLines].startLine, lines[displayedLines].endLine, 3);
    }
}




