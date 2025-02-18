#include "raylib.h"
#include "structures.h"



//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "rasterizer");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

// scene 1

    Structures::Mesh* cube = Structures::Mesh::createCube();

    Structures::Entity entity(cube, LibMath::Matrix4::createTransform(LibMath::Vector3(2.5f, 0.f, 2.f)));

    std::vector<Structures::Entity> entities = { entity };

    Structures::Scene scene1(entities);

    Structures::Texture tex(screenWidth, screenHeight, COLOR_BLACK);

    Structures::Rasterizer rasterizer;

    rasterizer.renderScene(&scene1, &tex);

// scene 2

    Structures::Vertex v1(-0.5f, -0.5f, 0.0f, COLOR_RED);
    //v1.setColor(COLOR_RED);
    Structures::Vertex v2(0.5f, -0.5f, 0.0f, COLOR_GREEN);
    //v2.setColor(COLOR_GREEN);
    Structures::Vertex v3(0.0f, 0.5f, 0.0f, COLOR_BLUE);
    //v3.setColor(COLOR_BLUE);

    Structures::Mesh triangleMesh({ v1, v2, v3 }, { 0, 1, 2 });

    entity = Structures::Entity(&triangleMesh, LibMath::Matrix4::createTransform(LibMath::Vector3(0.f, 0.f, 0.f)));

    entities = { entity };

    Structures::Scene scene2(entities);

    rasterizer.renderScene(&scene2, &tex, false);

    //Structures::Color color;
    

    while (!WindowShouldClose())
    {

        BeginDrawing();

        for (size_t i = 0; i < screenWidth; i++)
        {
            for (size_t j = 0; j < screenHeight; j++)
            {
                Structures::Color color = tex.m_pixels[j * tex.m_width + i];
                Color raylibColor = { color.m_r, color.m_g, color.m_b, color.m_a };
                DrawPixel(i, j, raylibColor);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}