#include "scene.h"

Structures::Scene::Scene(std::vector<Entity> entities)
{
    m_entities = entities;
}

Structures::Scene Structures::Scene::createProjectScene(Structures::Texture& tex)
{
    Structures::Scene scene;

    // entity 1 : cube

    Structures::Mesh* cube = Structures::Mesh::createCube();

    Structures::Entity entity(cube, LibMath::Matrix4::createTransform(LibMath::Vector3(2.5f, 5.f, -9.f)));

    scene.m_entities.push_back(entity);

    //// entity 2 : rainbowish triangle

    //Structures::Vertex v1(-0.5f, -0.5f, 0.0f, COLOR_RED);
    //Structures::Vertex v2(0.5f, -0.5f, 0.0f, COLOR_GREEN);
    //Structures::Vertex v3(0.0f, 0.5f, 0.0f, COLOR_BLUE);

    //Structures::Mesh* triangleMesh = new Structures::Mesh();
    //*triangleMesh = Structures::Mesh({ v1, v2, v3 }, { 0, 1, 2 });

    //entity = Structures::Entity(triangleMesh, LibMath::Matrix4::createTransform(LibMath::Vector3(0.f, 0.f, 0.f)));

    //scene.m_entities.push_back(entity);

    //// entity 3 : cube 2

    entity = Structures::Entity(cube, LibMath::Matrix4::createTransform(LibMath::Vector3(-2.f, 0.f, 2.f)));

    scene.m_entities.push_back(entity);

    //// entity 4: sphere

    Structures::Mesh* sphereMesh = Structures::Mesh::createSphere();

    entity = Structures::Entity(sphereMesh, LibMath::Matrix4::createTransform(LibMath::Vector3(-2.f, 0.f, -2.f)));

    scene.m_entities.push_back(entity);

    return scene;
}
