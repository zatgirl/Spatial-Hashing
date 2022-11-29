#include "spatialhash.h"

SpatialHashing::SpatialHashing(Vector2 _screenDimensions, int _amountCells){
    this->screenDimensions = _screenDimensions;
    this->amountCells = _amountCells;
    cell = new Cell[_amountCells * _amountCells];

    SpatialHashing::GenerateCells();
}

void SpatialHashing::RenderCells()
{
    SpatialHashing::DrawCells();
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

            cell[index].minBoundary = Vector2(tempMinX, tempMinY);
            cell[index].maxBoundary = Vector2(tempMinX + incrementoX, tempMinY + incrementoY);
            cell[index].color = Vector3(((rand() % 10) / 10.0), ((rand() % 10) / 10.0), ((rand() % 10) / 10.0));
            index ++;
        }
    }
}

void SpatialHashing::DrawCells(){
    for(int index = 0; index < this->amountCells * this->amountCells; index++)
    {
        CV::color(cell[index].color.x, cell[index].color.y, cell[index].color.z);
        CV::rectFill(cell[index].minBoundary, cell[index].maxBoundary);
    }
}
