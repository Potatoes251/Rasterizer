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

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        Structures::Mesh* cube = Structures::Mesh::createCube();

        Structures::Entity entity (cube, LibMath::Matrix4::createTransform(LibMath::Vector3(2.5f, 0.f, 2.f)));

        std::vector<Structures::Entity> entities = { entity };

        Structures::Scene scene (entities);

        Structures::Texture tex(screenWidth, screenHeight);

        Structures::Rasterizer rasterizer;

        rasterizer.renderScene(&scene, &tex);

        for (size_t i = 0; i < screenWidth; i++)
        {
            for (size_t j = 0; j < screenHeight; j++)
            {
                Structures::Color color = tex.m_pixels[j * screenWidth + i];
                Color raylibColor = { color.m_r, color.m_g, color.m_b, color.m_a };
                DrawPixel(i, j, raylibColor);
            }
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}