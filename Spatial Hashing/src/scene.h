#ifndef __SCENE__H___
#define __SCENE__H___

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>

#include "Vector2.h"
#include "gl_canvas2d.h"

class Scene
{
public:
    Vector2 screenDimensions;

    Scene();
    Scene(int _screenWidth, int _screenHeight);

    void render();
    void ShowFrames(float fps, int screenWidth, int screenHeight);

private:
    ~Scene();

    void ManagerMenu();
    void UI();
    void Buttons();
    void ShowInstructions();
};
#endif // __SCENE__H___
