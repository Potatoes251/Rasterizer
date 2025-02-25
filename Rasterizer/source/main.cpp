#define _USE_MATH_DEFINES
#include "raylib.h"
#include "rasterizer.h"
#include "scene.h"

#define SCREENWIDTH 800
#define SCREENHEIGHT 600

float g_rotation = 0.f;
bool g_wireframe = false;

int main(void)
{

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "rasterizer");

    SetTargetFPS(60);

    Structures::Rasterizer rasterizer;

    Structures::Texture tex(SCREENWIDTH, SCREENHEIGHT, COLOR_BLACK);

    Structures::Scene scene = Structures::Scene::createProjectScene(tex);

    LibMath::Matrix4 projectionMatrix = LibMath::Matrix4::perspective(M_PI / 2.f, 10.f / 10.f, .1f, 100.f);

    Structures::Camera camera = {LibMath::Vector3(0.f, 0.f, -1.f), 0.f, 0.f};

    /*LibMath::Matrix4 viewMatrix = Structures::createViewMatrix(LibMath::Vector3(0., 5.0f, 50.f), camera.m_pitch, camera.m_yaw);

   rasterizer.renderScene(&scene, &tex, projectionMatrix, viewMatrix);*/

    while (!WindowShouldClose())
    {
    	if (IsKeyPressed(KEY_F1)) // Check if F1 key is pressed
        {
            g_wireframe = !g_wireframe;
        }
        Structures::inputManager(camera);

        LibMath::Matrix4 viewMatrix = Structures::createViewMatrix(camera.m_position, camera.m_pitch, camera.m_yaw);
        
        g_rotation += 0.05f;
        scene.m_entities[0].m_transform = LibMath::Matrix4::createTransform(LibMath::Vector3(-2.5f, 0.f, -2.f), 
                                                                            LibMath::Radian(g_rotation));
        scene.m_entities[2].m_transform = LibMath::Matrix4::createTransform(LibMath::Vector3(2.5f, 0.f, -2.f),
                                                                            LibMath::Radian(g_rotation));
        scene.m_entities[3].m_transform = LibMath::Matrix4::createTransform(LibMath::Vector3(0.f, 2.5f, -2.f),
                                                                            LibMath::Radian(g_rotation), 
                                                                            LibMath::Vector3(2.f, 2.f, 2.f));
        scene.m_entities[4].m_transform = LibMath::Matrix4::createTransform(LibMath::Vector3(0.f, 2.5f, -2.f),
                                                                            LibMath::Radian(g_rotation));

        rasterizer.renderScene(&scene, &tex, projectionMatrix, viewMatrix);        

        tex.drawTexture(); // Draw the rasterized scene
    }

    for (int i = 0; i < scene.m_entities.size(); ++i)
    {
        if (scene.m_entities[i].m_texture)
        {
            delete scene.m_entities[i].m_texture;
        }
        if (scene.m_entities[i].m_mesh)
        {
            delete scene.m_entities[i].m_mesh;
        }
    }

    CloseWindow();

    return 0;
}