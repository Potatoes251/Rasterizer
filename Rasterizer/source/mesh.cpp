#include "mesh.h"

Structures::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<int> indices)
{
    m_vertices = vertices;
    m_indices = indices;
}

Structures::Mesh::Mesh() {}

Structures::Mesh* Structures::Mesh::createCube()
{
    Mesh* cubeMesh = new Mesh();

    static const Vertex coordinates[] = {
    { +0.5, +0.5, -0.5}, // Back-top-right
    {-0.5, +0.5, -0.5}, // Back-top-left
    {+0.5, -0.5, -0.5}, // Back-bottom-right
    {-0.5, -0.5, -0.5}, // Back-bottom-left
    {-0.5, -0.5, +0.5}, // Front-bottom-left
    {-0.5, +0.5, +0.5}, // Front-top-left
    {+0.5, +0.5, +0.5}, // Front-top-right
    {+0.5, -0.5, +0.5}, // Front-bottom-right
    };

    for (const auto& vertex : coordinates)
    {
        cubeMesh->m_vertices.push_back(Structures::Vertex(vertex));

    }

    cubeMesh->m_indices = {
        1, 2, 3, // back triable 1
        1, 0, 2, // back triangle 2
        4, 6, 5, // front triangle 1
        4, 7, 6, // front triangle 2
        7, 2, 0, // right triangle 1
        7, 0, 6, // right triangle 2
        5, 1, 3, // left triangle 1
        5, 3, 4, // left triangle 2
        0, 1, 5, // top triangle 1
        0, 5, 6, // top triangle 2
        3, 2, 7, // bottom triangle 1
        3, 7, 4 // bottom trianlge2
    };

    return cubeMesh;
}






