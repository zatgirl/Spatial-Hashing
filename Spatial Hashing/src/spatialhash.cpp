#include "spatialhash.h"

SpatialHashing::SpatialHashing(Vector2 _screenDimensions, int _amountCells)
{
    this->screenDimensions = _screenDimensions;
    this->amountCells = _amountCells;
    cells = new Cell[_amountCells * _amountCells];

    SpatialHashing::GenerateCells();
}

void SpatialHashing::RenderCells()
{
    SpatialHashing::DrawCells();
}

void SpatialHashing::UpdateSpatialHashing(int _amountCells)
{
    this->amountCells = _amountCells;
    cells = new Cell[_amountCells * _amountCells];

    SpatialHashing::GenerateCells();
}

void SpatialHashing::GenerateCells()
{
    int index = 0;
    int incrementoX = this->screenDimensions.x / this->amountCells;
    int incrementoY = this->screenDimensions.y / this->amountCells;

    for(int X = 0; X < this->amountCells; X ++)
    {
        for(int Y = 0; Y < this->amountCells; Y ++)
        {
            float tempMinX = X * incrementoX;
            float tempMinY = Y * incrementoY;

            cells[index].minBoundary = Vector2(tempMinX, tempMinY);
            cells[index].maxBoundary = Vector2(tempMinX + incrementoX, tempMinY + incrementoY);
            cells[index].color = Vector3(((rand() % 10) / 10.0), ((rand() % 10) / 10.0), ((rand() % 10) / 10.0));
            index ++;
        }
    }
}

void SpatialHashing::DrawCells()
{
    for(int index = 0; index < this->amountCells * this->amountCells; index++)
    {
        CV::color(cells[index].color.x, cells[index].color.y, cells[index].color.z);
        CV::rectFill(cells[index].minBoundary, cells[index].maxBoundary);
        CV::color(0);
        CV::text(cells[index].minBoundary.x, cells[index].maxBoundary.y - 10, index);
    }
}

void SpatialHashing::SearchLinesInCells(LinesManager::Line *linesTemp, int cellsCount)
{
    ///Primeiro busca em quais células então os vértices de cada linha
    for(int segment = 0; segment < this->amountLines; segment ++)
    {
        lines[segment].CellsPassedByLine.clear();
        for(int index = 0; index < cellsCount; index ++)
        {
            if(LinesManager::VertexInsideRectangle(lines[segment].startLine, cellsTemp[index]))
            {
                lines[segment].CellsPassedByLine.push_back(index);
            }
            if(LinesManager::VertexInsideRectangle(lines[segment].endLine, cellsTemp[index]))
            {
                lines[segment].CellsPassedByLine.push_back(index);
            }
        }
    }

    ///Checa com as células vizinhas se ocorreu intersecção
    for(int segment = 0; segment < this->amountLines; segment ++)
    {
        for(int index = 0; index < cellsCount; index ++)
        {
            Vector2 minBoudingLine = (lines[segment].CellsPassedByLine[0] < lines[segment].CellsPassedByLine[1]) ? cellsTemp[lines[segment].CellsPassedByLine[0]].minBoundary : cellsTemp[lines[segment].CellsPassedByLine[1]].minBoundary;
            Vector2 maxBoudingLine = (lines[segment].CellsPassedByLine[0] < lines[segment].CellsPassedByLine[1]) ? cellsTemp[lines[segment].CellsPassedByLine[1]].maxBoundary : cellsTemp[lines[segment].CellsPassedByLine[0]].maxBoundary;

            ///Testa se a célula está no limite de vizinhos
            if(LinesManager::CellAroundLine(cellsTemp[index].minBoundary, cellsTemp[index].maxBoundary, minBoudingLine, maxBoudingLine))
            {
                if((index != lines[segment].CellsPassedByLine[0]) && (index != lines[segment].CellsPassedByLine[1]))
                {
                    lines[segment].CellsPassedByLine.push_back(index);
                }
            }
        }
    }

    ///Puramente debug, apagar
    //printf("celulas ao redor da linha:\n");
    for(int segment = 0; segment < this->amountLines; segment ++)
    {
        for(int i = 0; i < lines[segment].CellsPassedByLine.size(); i ++)
        {
          // printf("%d\n", line[segment].CellsPassedByLine[i]);
        }
    }

    ///Percorre a bouding de celulas
    for(int segment = 0; segment < this->amountLines; segment ++)
    {
        for(int i = 0; i < lines[segment].CellsPassedByLine.size(); i ++)
        {
            std::vector<int> tempUsage = LinesManager::UsedCells(lines[segment].startLine, lines[segment].endLine, lines[segment].CellsPassedByLine, cellsTemp);
            lines[segment].CellsPassedByLine.clear();
            lines[segment].CellsPassedByLine = tempUsage;
        }
    }

    ///Puramente debug, apagar
    //printf("celulas em que REALMENTE passa:\n");
    for(int segment = 0; segment < this->amountLines; segment ++)
    {
        for(int i = 0; i < lines[segment].CellsPassedByLine.size(); i ++)
        {
      //     printf("%d\n", line[segment].usage[i]);
        }
    }

}

///Teste AABB
bool SpatialHashing::VertexInsideRectangle(Vector2 Vertex, LinesManager::Line cell)
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

bool SpatialHashing::CellAroundLine(Vector2 minBoudingCell, Vector2 maxBoudingCell, Vector2 minBoudingLine, Vector2 maxBoudingLine)
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

bool SpatialHashing::LineLineIntersection(Vector2 firstSegmentStart, Vector2 firstSegmentEnd, Vector2 secondSegmentStart, Vector2 secondSegmentEnd)
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

std::vector<int> SpatialHashing::UsedCells(Vector2 startLine, Vector2 endLine, std::vector<int> boudingCells, LinesManager::lines *lines)
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

void SpatialHashing::FeedHash()
{

}
