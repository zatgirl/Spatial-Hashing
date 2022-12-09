#include "Scene.h"

Scene::Scene()
{
}

Scene::Scene(int _screenWidth, int _screenHeight){
    this->screenDimensions.x  = _screenWidth;
    this->screenDimensions.y = _screenHeight;
}

Scene::~Scene()
{
}

void Scene::render()
{
    Scene::UI();
    Scene::ShowInstructions();
}

void Scene::UI(){
    ///Fundo
    CV::color(0.827, 0.827, 0.827);
    CV::rectFill(0,0,screenDimensions.x,screenDimensions.y);
}

void Scene::ShowFrames(float fps, int screenWidth, int screenHeight){
    CV::color(1,1,0);
    CV::rectFill(screenWidth-51,screenHeight-23, screenWidth, screenHeight-3);
    CV::color(0);
    CV::text(screenWidth-51,screenHeight-20, fps);
}

void Scene::ShowInstructions(){
    CV::color(0);
    CV::text(this->screenDimensions.x - 340, this->screenDimensions.y - 50,  "[Q] ADD CELLS");
    CV::text(this->screenDimensions.x - 340, this->screenDimensions.y - 70,  "[A] INC CELLS");
    CV::text(this->screenDimensions.x - 340, this->screenDimensions.y - 90,  "[W] ADD LINES");
    CV::text(this->screenDimensions.x - 340, this->screenDimensions.y - 110, "[S] INC LINES");
}
