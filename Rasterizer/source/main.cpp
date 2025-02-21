#include "raylib.h"

#include "rasterizer.h"
#include "scene.h"

float g_rotation = 0.f;
bool g_wireframe = false;

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
        if (IsKeyPressed(KEY_F1)) // Check if F1 key is pressed
        {
            g_wireframe = !g_wireframe;
        }

        g_rotation += 0.05f;
        scene.m_entities[0].m_transform = LibMath::Matrix4::createTransform(LibMath::Vector3(2.5f, 0.f, 2.f), 
                                                                            LibMath::Radian(g_rotation));
        scene.m_entities[2].m_transform = LibMath::Matrix4::createTransform(LibMath::Vector3(0.f, 0.f, 0.f),
                                                                            LibMath::Radian(g_rotation));
        rasterizer.renderScene(&scene, &tex, g_wireframe);

        tex.drawTexture();
    }
    CloseWindow();

    return 0;
}