/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2020
//
//  Versao 2.0
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <iomanip>

#include "gl_canvas2d.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Frames.h"
#include "line.h"
#include "spatialhash.h"

#include "Scene.h"


int screenWidth = 1800, screenHeight = 900;
bool click = false;
float fps;

int AMOUNT_LINES = 1000;
int AMOUNT_CELLS = 10; ///por orientação

Scene *scene;
Frames *frames;
LinesManager *linesManager;
SpatialHashing *spatialHashing;


///Obs.: Os segmentos de linha estão grossos, visualmente pode parecer uma falsa colisão!
void render()
{
    scene->render();
    spatialHashing->RenderCells();
    linesManager->RenderLines();

    time_t start, endd;
    time(&start);
    spatialHashing->LineLineIntersectionWithTable(linesManager->lines, AMOUNT_CELLS * AMOUNT_CELLS);
    time(&endd);
    fps = frames->getFrames();
    double time_exec = double(endd - start);

    #if 0
    ///Descomentar para ver os tempos
    std::cout << "FPS : " << fps << std::endl;
    std::cout << "Time of execution : " << (time_exec/CLOCKS_PER_SEC) << " seg " << std::endl;
    std::cout << "Lines : " << AMOUNT_LINES << std::endl;
    std::cout << "Hashs : " << (AMOUNT_CELLS*AMOUNT_CELLS) << std::endl;
    #endif
    fps = frames->getFrames();
    scene->ShowFrames(fps, screenWidth, screenHeight);
}

void keyboard(int key)
{
    switch(key){
        case 113: /// q
            spatialHashing->UpdateSpatialHashing(AMOUNT_CELLS += 2);
            spatialHashing->SpatialHashingUpdate(linesManager->lines, spatialHashing->cells, AMOUNT_CELLS*AMOUNT_CELLS, linesManager->amountLines);
            break;
        case 97:  /// a
            spatialHashing->UpdateSpatialHashing(AMOUNT_CELLS -= 2);
            spatialHashing->SpatialHashingUpdate(linesManager->lines, spatialHashing->cells, AMOUNT_CELLS*AMOUNT_CELLS, linesManager->amountLines);
            break;
        case 119: /// w
                linesManager->UpdateLines(AMOUNT_LINES += 1000);
                spatialHashing->SpatialHashingUpdate(linesManager->lines, spatialHashing->cells, AMOUNT_CELLS*AMOUNT_CELLS, linesManager->amountLines);

            break;
        case 115: /// s
            if(AMOUNT_LINES - 1000 > 0){
                linesManager->UpdateLines(AMOUNT_LINES -= 1000);
            }
            break;
        case 116: /// t > resize na tela
            spatialHashing->screenDimensions = Vector2(screenWidth - 350, screenHeight);
            spatialHashing->UpdateSpatialHashing(AMOUNT_CELLS += 1);
            linesManager->screenDimensions = Vector2(screenWidth - 350, screenHeight);
            spatialHashing->SpatialHashingUpdate(linesManager->lines, spatialHashing->cells, AMOUNT_CELLS*AMOUNT_CELLS, linesManager->amountLines);
            scene->screenDimensions = Vector2(screenWidth, screenHeight);
            break;
    }
}

void keyboardUp(int key)
{

}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{

}

int main(void)
{
    scene = new Scene(screenWidth, screenHeight);
    frames = new Frames();
    linesManager = new LinesManager(Vector2(screenWidth - 350, screenHeight), AMOUNT_LINES);
    spatialHashing = new SpatialHashing(Vector2(screenWidth - 350, screenHeight), AMOUNT_CELLS);

    linesManager->GenerateLines();
    spatialHashing->GenerateCells();

    spatialHashing->SpatialHashingUpdate(linesManager->lines, spatialHashing->cells, AMOUNT_CELLS*AMOUNT_CELLS, linesManager->amountLines);

    CV::init(&screenWidth, &screenHeight, "T2 - Spatial Hashing");
    CV::run();

    return 0;
}
