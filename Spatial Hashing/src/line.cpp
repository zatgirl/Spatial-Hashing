#include "line.h"

LinesManager::LinesManager(Vector2 _screenDimensions, int _amountLines){
    this->screenDimensions = _screenDimensions;
    this->amountLines = _amountLines;
    line = new Line[_amountLines];
    LinesManager::GenerateLines();
}

void LinesManager::RenderLines()
{
    LinesManager::ShowLines();
    LinesManager::LineLineIntersection();
}

void LinesManager::UpdateLines(int _amountLines)
{
    this->amountLines = _amountLines;
    LinesManager::GenerateLines();
}

///Voltar e arrumar, gerando apenas retas de 0° a 90°
void LinesManager::GenerateLines()
{
    for(int generatedLines = 0; generatedLines < this->amountLines; generatedLines ++)
    {
        line[generatedLines].startLine = Vector2(rand() % (int)this->screenDimensions.x, rand() % (int)this->screenDimensions.y);
        line[generatedLines].endLine = Vector2(rand() % 100 + line[generatedLines].startLine.x, rand() % 100 + line[generatedLines].startLine.y);
    }
}

void LinesManager::ShowLines()
{
    for(int displayedLines = 0; displayedLines < this->amountLines; displayedLines ++)
    {
        CV::color(0);
        CV::line(line[displayedLines].startLine, line[displayedLines].endLine, 3);
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

            x1 = line[secondSegment].endLine.x;    x2 = line[secondSegment].startLine.x;
            y1 = line[secondSegment].endLine.y;    y2 = line[secondSegment].startLine.y;
            x3 = line[firstSegment] .endLine.x;    x4 = line[firstSegment] .startLine.x;
            y3 = line[firstSegment] .endLine.y;    y4 = line[firstSegment] .startLine.y;

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
