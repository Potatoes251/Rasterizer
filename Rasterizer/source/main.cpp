#define _USE_MATH_DEFINES
#include "raylib.h"
#include "rasterizer.h"
#include "scene.h"

#define SCREENWIDTH 800
#define SCREENHEIGHT 600

int main(void)
{
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "rasterizer");

    SetTargetFPS(60);

    Structures::Texture tex(SCREENWIDTH, SCREENHEIGHT, COLOR_BLACK);

    Structures::Scene scene = Structures::Scene::createProjectScene(tex);

    LibMath::Matrix4 projectionMatrix = LibMath::Matrix4::perspective(M_PI / 2.f, 10.f / 10.f, .1f, 100.f);

    Structures::Camera camera = {LibMath::Vector3(0.f, 0.f, 10.f), 0.f, 0.f};

    /*LibMath::Matrix4 viewMatrix = Structures::createViewMatrix(LibMath::Vector3(0., 5.0f, 50.f), camera.m_pitch, camera.m_yaw);

   rasterizer.renderScene(&scene, &tex, projectionMatrix, viewMatrix);*/

    mainLoop(camera, tex, scene, projectionMatrix);

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