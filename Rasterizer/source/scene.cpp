#include "scene.h"
#include "memoryLeak.h"

Structures::Scene::Scene(std::vector<Entity> entities, std::vector<Light> lights)
{
    m_entities = entities;
    m_lights = lights;
}

Structures::Scene   Structures::Scene::createProjectScene(Structures::Texture& tex)
{
    Structures::Scene scene;

    // set the light

    Structures::Light light = Structures::Light(.2, 0.6, 0.4, LibMath::Vector3(400, 300, 500));
    scene.m_lights.push_back(light);

    // entity 1 : cube

    Structures::Mesh* cube = Structures::Mesh::createCube(nullptr, COLOR_PURPLE);
    Structures::Entity entity(cube);
    entity.m_alpha = 1.f;
    scene.m_entities.push_back(entity);

    //// entity 2 : rainbowish triangle

    Structures::Vertex v1(-0.5f, -0.5f, 0.0f, COLOR_RED);
    Structures::Vertex v2(0.5f, -0.5f, 0.0f, COLOR_GREEN);
    Structures::Vertex v3(0.0f, 0.5f, 0.0f, COLOR_BLUE);

    Structures::Mesh* triangleMesh = new Structures::Mesh();
    *triangleMesh = Structures::Mesh({ v1, v2, v3 }, { 0, 1, 2 });

    triangleMesh->setNormalsCube(triangleMesh);

    for (int i = 0; i < 3; ++i)
    {
        triangleMesh->m_vertices[i].m_normal = LibMath::Vector3(0,0,1);
        triangleMesh->m_vertices[i].m_normal.normalize();
    }

    entity = Structures::Entity(triangleMesh, LibMath::Matrix4::identity(), nullptr, 0.5f);
    entity.m_alpha = 1.f;
    scene.m_entities.push_back(entity);
    
    // entity 3 : textured cube

    Structures::Texture* cubeTexture = new Structures::Texture("../../Rasterizer/include/image.jpg");

    Structures::Mesh* cube2 = Structures::Mesh::createCube(cubeTexture, COLOR_MAGENTA);

    entity = Structures::Entity(cube2);
    entity.m_alpha = 1.f;
    scene.m_entities.push_back(entity);

    // entity 4 : cube behind next cube

    Structures::Mesh* cube4 = Structures::Mesh::createCube(nullptr, COLOR_GOLD);

    entity = Structures::Entity(cube4);
    entity.m_alpha = 1.f;
    scene.m_entities.push_back(entity);

    // entity 5 : cube in front previous cube

    Structures::Mesh* cube3 = Structures::Mesh::createCube(nullptr, COLOR_CYAN);

    entity = Structures::Entity(cube3);
    entity.m_alpha = .5f;
    scene.m_entities.push_back(entity);

    // entity 6 : sphere
    
    Structures::Mesh* sphereMesh = Structures::Mesh::createSphere();

    entity = Structures::Entity(sphereMesh);

    scene.m_entities.push_back(entity);


    return scene;
}
