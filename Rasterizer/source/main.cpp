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

    LibMath::Matrix4 projectionMatrix = LibMath::Matrix4::perspective(M_PI / 2.f, 10.f / 10.f, .1f, 100.f);

    Structures::Camera camera = {LibMath::Vector3(0.f, 0.f, -1.f), 0.f, 0.f};

    /*LibMath::Matrix4 viewMatrix = Structures::createViewMatrix(LibMath::Vector3(0., 5.0f, 50.f), camera.m_pitch, camera.m_yaw);

   rasterizer.renderScene(&scene, &tex, projectionMatrix, viewMatrix);*/

    while (!WindowShouldClose())
    {
        Structures::inputManager(camera);

        LibMath::Matrix4 viewMatrix = Structures::createViewMatrix(camera.m_position, camera.m_pitch, camera.m_yaw);

        rasterizer.renderScene(&scene, &tex, projectionMatrix, viewMatrix);        

        tex.drawTexture(); // Draw the rasterized scene
    }
    CloseWindow();

    return 0;
}