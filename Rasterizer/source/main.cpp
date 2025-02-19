#include "raylib.h"

#include "rasterizer.h"
#include "scene.h"

float rotation = 0.f;


int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "rasterizer");

    SetTargetFPS(60);

    Structures::Rasterizer rasterizer;

    Structures::Texture tex(800, 600, COLOR_BLACK);

    Structures::Scene scene = Structures::Scene::createProjectScene(tex);

    

    while (!WindowShouldClose())
    {
        rotation += 0.05f;
        scene.m_entities[0].m_transform = LibMath::Matrix4::createTransform(LibMath::Vector3(2.5f, 0.f, 2.f), 
                                                                            LibMath::Radian(rotation));
        rasterizer.renderScene(&scene, &tex);

        tex.drawTexture();
    }
    CloseWindow();

    return 0;
}