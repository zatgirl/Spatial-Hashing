#include "spatialhash.h"

SpatialHashing::SpatialHashing(Vector2 _screenDimensions, int _amountCells)
{
    this->screenDimensions = _screenDimensions;
    this->amountCells = _amountCells;
    cells = new Cell[_amountCells * _amountCells];
    hashT = new Hash();

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

bool SpatialHashing::VertexInsideRectangle(Vector2 Vertex, SpatialHashing::Cell cell)
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

void SpatialHashing::LineLineIntersectionWithMark(Vector2 firstSegmentStart, Vector2 firstSegmentEnd, Vector2 secondSegmentStart, Vector2 secondSegmentEnd)
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
        Vector2 pointIntersection = Vector2(x1 + (t*(x2 - x1)), y1 + (t*(y2 - y1)));
        CV::color(2);
        CV::circle(pointIntersection, 5, 15, 2);
    }
}

std::vector<int> SpatialHashing::UsedCells(Vector2 startLine, Vector2 endLine, std::vector<int> boudingCells, SpatialHashing::Cell *cell)
{
    std::vector<int> usage;
    for(int index = 0; index < boudingCells.size(); index ++)
    {
        Vector2 v0 = cell[boudingCells[index]].minBoundary;
        Vector2 v1 = Vector2(cell[boudingCells[index]].maxBoundary.x, cell[boudingCells[index]].minBoundary.y);
        Vector2 v2 = cell[boudingCells[index]].maxBoundary;
        Vector2 v3 = Vector2(cell[boudingCells[index]].minBoundary.x, cell[boudingCells[index]].maxBoundary.y);

        if(SpatialHashing::LineLineIntersection(startLine, endLine, v0, v1))
        {
            usage.push_back(boudingCells[index]);
            continue;
        }
        if(SpatialHashing::LineLineIntersection(startLine, endLine, v1, v2))
        {
            usage.push_back(boudingCells[index]);
            continue;
        }
        if(SpatialHashing::LineLineIntersection(startLine, endLine, v2, v3))
        {
            usage.push_back(boudingCells[index]);
            continue;
        }
        if(SpatialHashing::LineLineIntersection(startLine, endLine, v3, v0))
        {
            usage.push_back(boudingCells[index]);
            continue;
        }
    }
    return usage;
}

void SpatialHashing::SpatialHashingUpdate(LinesManager::Line *lines, SpatialHashing::Cell *cells, int cellsCount, int amountLines)
{
    SpatialHashing::DestructStructHash();
    ///Primeiro for do artigo
    for (int segment = 0; segment < amountLines; segment ++)
    {
        std::vector<int> cellsPassedByLineTemp = SpatialHashing::CellsPassedByLine(lines[segment], cellsCount, amountLines);
        for(int indexCellsPassed = 0; indexCellsPassed < cellsPassedByLineTemp.size(); indexCellsPassed ++)
        {
            lines[segment].CellsPassedByLine[indexCellsPassed] = cellsPassedByLineTemp[indexCellsPassed];
            hashT->usage[cellsPassedByLineTemp[indexCellsPassed]] ++;
        }
        lines[segment].AmountCellsPassed = cellsPassedByLineTemp.size();
    }

    ///Segundo for do artigo
    for (int cell = 0, accum = 0; cell < cellsCount; cell ++)
    {
        hashT->initialIndex[cell] = accum;
        accum += hashT->usage[cell];
        hashT->finalIndex[cell] = accum;
    }

    ///Terceiro for do artigo
    for (int segment = 0; segment < amountLines; segment ++)
    {
        for(int cell = 0; cell < lines[segment].AmountCellsPassed; cell ++)
        {
            hashT->hashTable[hashT->finalIndex[lines[segment].CellsPassedByLine[cell]] - 1] = segment;
            hashT->finalIndex[lines[segment].CellsPassedByLine[cell]] --;
        }
    }
}

std::vector<int> SpatialHashing::CellsPassedByLine (LinesManager::Line line, int cellsCount, int amountLines)
{
    ///REFATORAR, tirar funções pra fora ********************************************
    ///Busca em quais células estão os vértices de cada linha
    std::vector<int> CellsPassedByLine;
    for(int index = 0; index < cellsCount; index ++)
    {
        if(SpatialHashing::VertexInsideRectangle(line.startLine, SpatialHashing::cells[index]))
        {
            CellsPassedByLine.push_back(index);
        }
        if(SpatialHashing::VertexInsideRectangle(line.endLine, SpatialHashing::cells[index]))
        {
            if(CellsPassedByLine.size() > 0)
            {
                if(CellsPassedByLine[0] == index)
                {
                    return CellsPassedByLine;
                }
            }
            else
            {
                CellsPassedByLine.push_back(index);
            }
        }
    }

    if((CellsPassedByLine.size() > 2) || (CellsPassedByLine.size() == 0)){
        return CellsPassedByLine;
    }
    else
    {
    ///Checa com as células vizinhas se ocorreu intersecção
    for(int index = 0; index < cellsCount; index ++)
    {
        Vector2 minBoudingLine = (CellsPassedByLine[0] < CellsPassedByLine[1]) ? cells[CellsPassedByLine[0]].minBoundary : cells[CellsPassedByLine[1]].minBoundary;
        Vector2 maxBoudingLine = (CellsPassedByLine[0] < CellsPassedByLine[1]) ? cells[CellsPassedByLine[1]].maxBoundary : cells[CellsPassedByLine[0]].maxBoundary;

        ///Testa se a célula está no limite de vizinhos
        if(SpatialHashing::CellAroundLine(cells[index].minBoundary, cells[index].maxBoundary, minBoudingLine, maxBoudingLine))
        {
            if((index != CellsPassedByLine[0]) && (index != CellsPassedByLine[1]))
            {
                CellsPassedByLine.push_back(index);
            }
        }
    }

    std::vector<int> tempUsage = SpatialHashing::UsedCells(line.startLine, line.endLine, CellsPassedByLine, SpatialHashing::cells);
    CellsPassedByLine.clear();
    CellsPassedByLine = tempUsage;

    return CellsPassedByLine;
    }
}

void SpatialHashing::LineLineIntersectionWithTable(LinesManager::Line *lines, int cellsCount)
{
    int intersection = 0;
    ///Todas x Todas linhas dentro de cada celula
    for (int cell = 0; cell < cellsCount; cell ++)
    {
        int initI = hashT->initialIndex[cell];
        int finalI = hashT->initialIndex[cell]+hashT->usage[cell];
        for (int firstSegmentInCell = initI; firstSegmentInCell < finalI; firstSegmentInCell ++)
        {
            Vector2 firstSegmentP1 = lines[hashT->hashTable[firstSegmentInCell]].startLine;
            Vector2 firstSegmentP2 = lines[hashT->hashTable[firstSegmentInCell]].endLine;
            for (int secondSegmentInCell = initI; secondSegmentInCell < finalI; secondSegmentInCell ++)
            {
                Vector2 secondSegmentP1 = lines[hashT->hashTable[secondSegmentInCell]].startLine;
                Vector2 secondSegmentP2 = lines[hashT->hashTable[secondSegmentInCell]].endLine;
                if(firstSegmentInCell != secondSegmentInCell)
                {
                    SpatialHashing::LineLineIntersectionWithMark(firstSegmentP1, firstSegmentP2, secondSegmentP1, secondSegmentP2);
                }
            }
        }
    }
}

void SpatialHashing::DestructStructHash(){
    memset(hashT->       usage, 0, sizeof(hashT->       usage));
    memset(hashT->initialIndex, 0, sizeof(hashT->initialIndex));
    memset(hashT->  finalIndex, 0, sizeof(hashT->  finalIndex));
    memset(hashT->   hashTable, 0, sizeof(hashT->   hashTable));
}
