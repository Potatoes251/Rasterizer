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

    Structures::Camera camera = {LibMath::Vector3(0.f, 0.f, 1.f), 0.f, 0.f};

    Structures::mainLoop(camera, tex, scene, projectionMatrix);

    return 0;
}