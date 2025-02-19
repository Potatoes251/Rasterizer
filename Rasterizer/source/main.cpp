#include "raylib.h"

#include "rasterizer.h"
#include "scene.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "rasterizer");

    SetTargetFPS(60);

    Structures::Rasterizer rasterizer;

    Structures::Texture tex(800, 600, COLOR_BLACK);

    Structures::Scene scene = Structures::Scene::createProjectScene(tex);

    rasterizer.renderScene(&scene, &tex);

    while (!WindowShouldClose())
    {
        tex.drawTexture();
    }
    CloseWindow();

    return 0;
}