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

Structures::Mesh* Structures::Mesh::createCube(Texture* tex, Structures::Color color)
{
    Mesh* cubeMesh = new Mesh();

    cubeMesh->m_texture = tex;

    // Define the vertices of the cube with texture coordinates
    const Vertex coordinates[] = {
        // Back face
        { +0.5, +0.5, -0.5, 1.0f, 1.0f, color}, // Top-right
        {-0.5, +0.5, -0.5, 0.0f, 1.0f, color}, // Top-left
        {+0.5, -0.5, -0.5, 1.0f, 0.0f, color}, // Bottom-right
        {-0.5, -0.5, -0.5, 0.0f, 0.0f, color}, // Bottom-left

        // Front face
        {-0.5, -0.5, +0.5, 0.0f, 0.0f, color}, // Bottom-left
        {-0.5, +0.5, +0.5, 0.0f, 1.0f, color}, // Top-left
        {+0.5, +0.5, +0.5, 1.0f, 1.0f, color}, // Top-right
        {+0.5, -0.5, +0.5, 1.0f, 0.0f, color}, // Bottom-right

        // Left face
        {-0.5, +0.5, -0.5, 1.0f, 1.0f, color}, // Top-right
        {-0.5, +0.5, +0.5, 0.0f, 1.0f, color}, // Top-left
        {-0.5, -0.5, -0.5, 1.0f, 0.0f, color}, // Bottom-right
        {-0.5, -0.5, +0.5, 0.0f, 0.0f, color}, // Bottom-left

        // Right face
        {+0.5, +0.5, -0.5, 0.0f, 1.0f, color}, // Top-right
        {+0.5, +0.5, +0.5, 1.0f, 1.0f, color}, // Top-left
        {+0.5, -0.5, -0.5, 0.0f, 0.0f, color}, // Bottom-right
        {+0.5, -0.5, +0.5, 1.0f, 0.0f, color}, // Bottom-left

        // Top face
        {+0.5, +0.5, +0.5, 0.0f, 1.0f, color}, // Top-right
        {-0.5, +0.5, +0.5, 1.0f, 1.0f, color}, // Top-left
        {+0.5, +0.5, -0.5, 0.0f, 0.0f, color}, // Bottom-right
        {-0.5, +0.5, -0.5, 1.0f, 0.0f, color}, // Bottom-left

        // Bottom face
        {+0.5, -0.5, -0.5, 0.0f, 1.0f, color}, // Top-right
        {-0.5, -0.5, -0.5, 1.0f, 1.0f, color}, // Top-left
        {+0.5, -0.5, +0.5, 0.0f, 0.0f, color}, // Bottom-right
        {-0.5, -0.5, +0.5, 1.0f, 0.0f, color}, // Bottom-left
    };

    // Add the vertices to the mesh (with texture coordinates)
    for (const auto& vertex : coordinates)
    {
        cubeMesh->m_vertices.push_back(vertex);
    }

    // Define the indices for each face of the cube
    cubeMesh->m_indices = {
        // Back face
        0, 2, 1, 
        1, 2, 3,
        // Front face
        4, 6, 5, 
        4, 7, 6,
        // Left face
        8, 10, 9, 
        10, 11, 9,
        // Right face
        12, 13, 14, 
        14, 13, 15,
        // Top face
        16, 18, 17, 
        18, 19, 17,
        // Bottom face
        20, 22, 21,
        22, 23, 21
    };

    setNormalsFace(cubeMesh);

    return cubeMesh;
}



void Structures::Mesh::setNormals(Mesh* cubeMesh)
{
    // Calculate the normals for each vertex
    for (int i = 0; i < cubeMesh->m_vertices.size(); ++i)
    {
        cubeMesh->m_vertices[i].m_normal = cubeMesh->m_vertices[i].m_position;
        cubeMesh->m_vertices[i].m_normal.normalize();
    }
}

Structures::Mesh* Structures::Mesh::createCube(Structures::Color color)
{
    Mesh* cubeMesh = new Mesh();

    const Vertex coordinates[] = {
    {+0.5, +0.5, -0.5, color}, // Back-top-right
    {-0.5, +0.5, -0.5, color}, // Back-top-left
    {+0.5, -0.5, -0.5, color}, // Back-bottom-right
    {-0.5, -0.5, -0.5, color}, // Back-bottom-left
    {-0.5, -0.5, +0.5, color}, // Front-bottom-left
    {-0.5, +0.5, +0.5, color}, // Front-top-left
    {+0.5, +0.5, +0.5, color}, // Front-top-right
    {+0.5, -0.5, +0.5, color}, // Front-bottom-right
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

    setNormalsFace(cubeMesh);

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

void Structures::Mesh::setNormalsFace(Mesh* cubeMesh)
{
    for (int i = 0; i < cubeMesh->m_indices.size(); i += 3)
    {
        LibMath::Vector3 v1 = cubeMesh->m_vertices[cubeMesh->m_indices[i]].m_position;
        LibMath::Vector3 v2 = cubeMesh->m_vertices[cubeMesh->m_indices[i + 1]].m_position;
        LibMath::Vector3 v3 = cubeMesh->m_vertices[cubeMesh->m_indices[i + 2]].m_position;

        LibMath::Vector3 v1v2 = v2 - v1;
        LibMath::Vector3 v1v3 = v3 - v1;

        LibMath::Vector3 normal = v1v2.cross(v1v3);

        cubeMesh->m_vertices[cubeMesh->m_indices[i]].m_normal = normal;
        cubeMesh->m_vertices[cubeMesh->m_indices[i + 1]].m_normal = normal;
        cubeMesh->m_vertices[cubeMesh->m_indices[i + 2]].m_normal = normal;
    }
}
