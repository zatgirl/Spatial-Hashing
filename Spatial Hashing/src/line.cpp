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
   // LinesManager::LineLineIntersection();
}

void LinesManager::UpdateLines(int _amountLines)
{
    this->amountLines = _amountLines;
    line = new Line[_amountLines];
    LinesManager::GenerateLines();
}

///Voltar e arrumar, gerando apenas retas de 0° a 90°
void LinesManager::GenerateLines()
{
    for(int generatedLines = 0; generatedLines < this->amountLines; generatedLines ++)
    {
        line[generatedLines].startLine = Vector2(rand() % (int)this->screenDimensions.x, rand() % (int)this->screenDimensions.y);
        line[generatedLines].endLine = Vector2(rand() % 1000 + line[generatedLines].startLine.x, rand() % 700 + line[generatedLines].startLine.y);
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

void LinesManager::SearchLinesInCells(SpatialHashing::Cell *cellsTemp, int cellsCount)
{
    int amountLinesInCell[cellsCount];

    ///Primeiro busca em quais células então os vértices de cada linha
    for(int segment = 0; segment < this->amountLines; segment ++)
    {
        line[segment].usage.clear();
        for(int index = 0; index < cellsCount; index ++)
        {
            if(LinesManager::VertexInsideRectangle(line[segment].startLine, cellsTemp[index]))
            {
                line[segment].usage.push_back(index);
            }
            if(LinesManager::VertexInsideRectangle(line[segment].endLine, cellsTemp[index]))
            {
                line[segment].usage.push_back(index);
            }
        }
    }

    ///Checa com as células vizinhas se ocorreu intersecção
    for(int segment = 0; segment < this->amountLines; segment ++)
    {
        for(int index = 0; index < cellsCount; index ++)
        {
            Vector2 minBoudingLine = (line[segment].usage[0] < line[segment].usage[1]) ? cellsTemp[line[segment].usage[0]].minBoundary : cellsTemp[line[segment].usage[1]].minBoundary;
            Vector2 maxBoudingLine = (line[segment].usage[0] < line[segment].usage[1]) ? cellsTemp[line[segment].usage[1]].maxBoundary : cellsTemp[line[segment].usage[0]].maxBoundary;

            ///Testa se a célula está no limite de vizinhos
            if(LinesManager::CellAroundLine(cellsTemp[index].minBoundary, cellsTemp[index].maxBoundary, minBoudingLine, maxBoudingLine))
            {
                if((index != line[segment].usage[0]) && (index != line[segment].usage[1]))
                {
                    line[segment].usage.push_back(index);
                }
            }
        }
    }

    ///Puramente debug, apagar
    printf("celulas ao redor da linha:\n");
    for(int segment = 0; segment < this->amountLines; segment ++)
    {
        for(int i = 0; i < line[segment].usage.size(); i ++)
        {
           printf("%d\n", line[segment].usage[i]);
        }
    }

    ///Percorre a bouding de celulas
    for(int segment = 0; segment < this->amountLines; segment ++)
    {
        for(int i = 0; i < line[segment].usage.size(); i ++)
        {
            std::vector<int> tempUsage = LinesManager::UsedCells(line[segment].startLine, line[segment].endLine, line[segment].usage, cellsTemp);
            line[segment].usage.clear();
            line[segment].usage = tempUsage;
        }
    }

    ///Puramente debug, apagar
    printf("celulas em que REALMENTE passa:\n");
    for(int segment = 0; segment < this->amountLines; segment ++)
    {
        for(int i = 0; i < line[segment].usage.size(); i ++)
        {
           printf("%d\n", line[segment].usage[i]);
        }
    }

}

///Teste AABB
bool LinesManager::VertexInsideRectangle(Vector2 Vertex, SpatialHashing::Cell cell)
{
    if((Vertex.x > cell.minBoundary.x) && (Vertex.x < cell.maxBoundary.x))
    {
        if((Vertex.y > cell.minBoundary.y) && (Vertex.y < cell.maxBoundary.y))
        {
            return true;
        }
    }
    return false;
}

bool LinesManager::CellAroundLine(Vector2 minBoudingCell, Vector2 maxBoudingCell, Vector2 minBoudingLine, Vector2 maxBoudingLine)
{

    if((minBoudingCell.x >= minBoudingLine.x) && (minBoudingCell.y >= minBoudingLine.y))
    {
        if((maxBoudingCell.x <= maxBoudingLine.x) && (maxBoudingCell.y <= maxBoudingLine.y))
        {
            return true;
        }
    }
    return false;
}

bool LinesManager::LineLineIntersection(Vector2 firstSegmentStart, Vector2 firstSegmentEnd, Vector2 secondSegmentStart, Vector2 secondSegmentEnd)
{
    double t, u, x1, x2, x3, x4, y1, y2, y3, y4;

    x1 = secondSegmentEnd.x;    x2 = secondSegmentStart.x;
    y1 = secondSegmentEnd.y;    y2 = secondSegmentStart.y;
    x3 = firstSegmentEnd.x;     x4 = firstSegmentStart.x;
    y3 = firstSegmentEnd.y;     y4 = firstSegmentStart.y;

    t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
    u = ((x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));

    if ((t >= 0 && t <= 1) && (u >= 0 && u <= 1))
    {
        return true;
    }
    return false;
}

std::vector<int> LinesManager::UsedCells(Vector2 startLine, Vector2 endLine, std::vector<int> boudingCells, SpatialHashing::Cell *cell)
{
    std::vector<int> usage;
    for(int index = 0; index < boudingCells.size(); index ++)
    {
        Vector2 v0 = cell[boudingCells[index]].minBoundary;
        Vector2 v1 = Vector2(cell[boudingCells[index]].maxBoundary.x, cell[boudingCells[index]].minBoundary.y);
        Vector2 v2 = cell[boudingCells[index]].maxBoundary;
        Vector2 v3 = Vector2(cell[boudingCells[index]].minBoundary.x, cell[boudingCells[index]].maxBoundary.y);

        if(LinesManager::LineLineIntersection(startLine, endLine, v0, v1))
        {
            usage.push_back(boudingCells[index]);
            continue;
        }
        if(LinesManager::LineLineIntersection(startLine, endLine, v1, v2))
        {
            usage.push_back(boudingCells[index]);
            continue;
        }
        if(LinesManager::LineLineIntersection(startLine, endLine, v2, v3))
        {
            usage.push_back(boudingCells[index]);
            continue;
        }
        if(LinesManager::LineLineIntersection(startLine, endLine, v3, v0))
        {
            usage.push_back(boudingCells[index]);
            continue;
        }
    }
    return usage;
}
