#define _USE_MATH_DEFINES

#ifndef _CMATH_
#include <cmath>
#endif // !_CMATH_
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

Structures::Mesh* Structures::Mesh::createSphere(int widthSegments, int heightSegments, float radius)
{
    std::vector<Vertex> vertices;
    std::vector<int> indices;

    // Génération des sommets
    for (int height = 0; height <= heightSegments; ++height)
    {
        float theta = height * M_PI / heightSegments;  // De 0 à Pi
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);

        for (int width = 0; width <= widthSegments; ++width)
        {
            float phi = width * 2.0f * M_PI / widthSegments;  // De 0 à 2Pi
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            LibMath::Vector3 position = {
                radius * cosPhi * sinTheta,
                radius * sinPhi * sinTheta,
                radius * cosTheta
            };

            vertices.emplace_back(position, COLOR_BLUE);
        }
    }

    // Génération des indices
    for (int height = 0; height < heightSegments; ++height)
    {
        for (int width = 0; width < widthSegments; ++width)
        {
            int first = (height * (widthSegments + 1)) + width;
            int second = first + widthSegments + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    return new Mesh(vertices, indices);
}







