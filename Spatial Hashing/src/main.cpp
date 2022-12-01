/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2020
//
//  Versao 2.0
// *********************************************************************/
///Objetivos
///
///

///Implementações:
///


#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

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

int AMOUNT_LINES = 2;
int AMOUNT_CELLS = 3; ///por orientação

Scene *scene;
Frames *frames;
LinesManager *linesManager;
SpatialHashing *spatialHashing;

void render()
{
    scene->render();
    spatialHashing->RenderCells();

    linesManager->RenderLines();

    fps = frames->getFrames();
    scene->ShowFrames(fps, screenWidth, screenHeight);
}

void keyboard(int key)
{
    switch(key){
        case 113: /// q
            spatialHashing->UpdateSpatialHashing(AMOUNT_CELLS +=1);
            spatialHashing->SearchLinesInCells(linesManager->lines, AMOUNT_CELLS*AMOUNT_CELLS);
            break;
        case 97:  /// a
            spatialHashing->UpdateSpatialHashing(AMOUNT_CELLS -= 1);
            spatialHashing->SearchLinesInCells(linesManager->lines, AMOUNT_CELLS*AMOUNT_CELLS);
            break;
        case 119: /// w
            linesManager->UpdateLines(AMOUNT_LINES += 100);
            break;
        case 115: /// s
            if(AMOUNT_LINES - 1 > 0){
                linesManager->UpdateLines(AMOUNT_LINES -= 100);
            }
            break;
        case 116: /// t > resize na tela
            spatialHashing->screenDimensions = Vector2(screenWidth - 350, screenHeight);
            spatialHashing->UpdateSpatialHashing(AMOUNT_CELLS += 1);
            linesManager->screenDimensions = Vector2(screenWidth - 350, screenHeight);
            spatialHashing->SearchLinesInCells(linesManager->lines, AMOUNT_CELLS*AMOUNT_CELLS);
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

    spatialHashing->SearchLinesInCells(linesManager->lines, AMOUNT_CELLS*AMOUNT_CELLS);

    CV::init(&screenWidth, &screenHeight, "T2 - Spatial Hashing");
    CV::run();

    return 0;
}
