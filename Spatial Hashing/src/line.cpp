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
    //LinesManager::LineLineIntersection();
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

        endX = rand() % 100 + lines[generatedLines].startLine.x;
        endX = (endX > (int)this->screenDimensions.x) ? (int)this->screenDimensions.x : endX;

        endY = rand() % 100 + lines[generatedLines].startLine.y;
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

void LinesManager::LineLineIntersection()
{
    ///Todos contra Todos
    for(int firstSegment = 0; firstSegment < this->amountLines; firstSegment++)
    {
        for(int secondSegment = 0; secondSegment < this->amountLines; secondSegment++)
        {
            double t, u, x1, x2, x3, x4, y1, y2, y3, y4;

            x1 = lines[secondSegment].endLine.x;    x2 = lines[secondSegment].startLine.x;
            y1 = lines[secondSegment].endLine.y;    y2 = lines[secondSegment].startLine.y;
            x3 = lines[firstSegment] .endLine.x;    x4 = lines[firstSegment] .startLine.x;
            y3 = lines[firstSegment] .endLine.y;    y4 = lines[firstSegment] .startLine.y;

            t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
            u = ((x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));

            if ((t >= 0 && t <= 1) && (u >= 0 && u <= 1))
            {
                Vector2 pointIntersection = Vector2(x1 + (t*(x2 - x1)), y1 + (t*(y2 - y1)));
                CV::color(2);
                CV::circle(pointIntersection, 5, 15, 2);
            }
        }
    }
}




