#define _USE_MATH_DEFINES
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

    LibMath::Matrix4 projectionMatrix = LibMath::Matrix4::perspective(M_PI / 1.5f, 16.f / 9.f, 0.1f, 100.f);



    LibMath::Matrix4 viewMatrix = Structures::createViewMatrix(LibMath::Vector3(0.f, 0.f, 0.f));

    rasterizer.renderScene(&scene, &tex, projectionMatrix, viewMatrix);

    while (!WindowShouldClose())
    {
        tex.drawTexture();
    }
    CloseWindow();

    return 0;
}