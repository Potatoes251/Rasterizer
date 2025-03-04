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

Structures::Mesh*       Structures::Mesh::createCube(Texture* tex, Structures::Color color)
{
    Mesh*       cubeMesh = new Mesh();

    cubeMesh->m_texture = tex;

    // Define the vertices of the cube with texture coordinates
    const Vertex coordinates[] = {
        // Back face
        { +0.5, +0.5, -0.5, 0.0f, 1.0f, color}, // back-top-right
        {-0.5, +0.5, -0.5, 1.0f, 1.0f, color}, // back-top-left
        {+0.5, -0.5, -0.5, 0.0f, 0.0f, color}, // back-bottom-right
        {-0.5, -0.5, -0.5, 1.0f, 0.0f, color}, // back-bottom-left

        // Front face
        {-0.5, -0.5, +0.5, 0.0f, 0.0f, color}, // front-bottom-left
        {-0.5, +0.5, +0.5, 0.0f, 1.0f, color}, // front-top-left
        {+0.5, +0.5, +0.5, 1.0f, 1.0f, color}, // front-top-right
        {+0.5, -0.5, +0.5, 1.0f, 0.0f, color}, // front-bottom-right

        // Left face
        {-0.5, +0.5, -0.5, 0.0f, 1.0f, color}, // back-top-left
        {-0.5, +0.5, +0.5, 1.0f, 1.0f, color}, // front-top-left
        {-0.5, -0.5, -0.5, 0.0f, 0.0f, color}, // back-bottom-left
        {-0.5, -0.5, +0.5, 1.0f, 0.0f, color}, // front-bottom-left

        // Right face
        {+0.5, +0.5, -0.5, 1.0f, 1.0f, color}, // back-top-right
        {+0.5, +0.5, +0.5, 0.0f, 1.0f, color}, // front-top-right
        {+0.5, -0.5, -0.5, 1.0f, 0.0f, color}, // back-bottom-right
        {+0.5, -0.5, +0.5, 0.0f, 0.0f, color}, // front-bottom-right

        // Top face
        {+0.5, +0.5, +0.5, 1.0f, 1.0f, color}, // front-top-right
        {-0.5, +0.5, +0.5, 0.0f, 1.0f, color}, // front-top-left
        {+0.5, +0.5, -0.5, 1.0f, 0.0f, color}, // back-top-right
        {-0.5, +0.5, -0.5, 0.0f, 0.0f, color}, // back-top-left

        // Bottom face
        {+0.5, -0.5, -0.5, 0.0f, 1.0f, color}, // back-bottom-right
        {-0.5, -0.5, -0.5, 1.0f, 1.0f, color}, // back-bottom-left
        {+0.5, -0.5, +0.5, 0.0f, 0.0f, color}, // front-bottom-right
        {-0.5, -0.5, +0.5, 1.0f, 0.0f, color}, // front-bottom-left
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

    setNormalsCube(cubeMesh);

    return cubeMesh;
}

void        Structures::Mesh::setNormalsCube(Mesh* cubeMesh)    // calculate the normals per face
{
    LibMath::Vector3    v1;
    LibMath::Vector3    v2;
    LibMath::Vector3    v3;
    LibMath::Vector3    v1v2;
    LibMath::Vector3    v1v3;
    LibMath::Vector3    normal;

    for (int i = 0; i < cubeMesh->m_indices.size(); i += 3)
    {
        v1 = cubeMesh->m_vertices[cubeMesh->m_indices[i]].m_position;
        v2 = cubeMesh->m_vertices[cubeMesh->m_indices[i + 1]].m_position;
        v3 = cubeMesh->m_vertices[cubeMesh->m_indices[i + 2]].m_position;

        v1v2 = v2 - v1;
        v1v3 = v3 - v1;

        normal = v1v2.cross(v1v3); // calculate the face normal

        cubeMesh->m_vertices[cubeMesh->m_indices[i]].m_normal = normal; // put it in the vertex
        cubeMesh->m_vertices[cubeMesh->m_indices[i + 1]].m_normal = normal;
        cubeMesh->m_vertices[cubeMesh->m_indices[i + 2]].m_normal = normal;
    }
}

Structures::Mesh*       Structures::Mesh::createSphere(int widthSegments, int heightSegments, float radius)
{
    std::vector<Vertex>     vertices;
    std::vector<int>        indices;

    // Génération des sommets
    for (int height = 0; height <= heightSegments; ++height)
    {
        float   theta = height * M_PI / heightSegments;  // De 0 à Pi
        float   sinTheta = sin(theta);
        float   cosTheta = cos(theta);

        for (int width = 0; width <= widthSegments; ++width)
        {
            float   phi = width * 2.0f * M_PI / widthSegments;  // De 0 à 2Pi
            float   sinPhi = sin(phi);
            float   cosPhi = cos(phi);

            LibMath::Vector3    position = {
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
            int     first = (height * (widthSegments + 1)) + width;
            int     second = first + widthSegments + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }
    Mesh*   SphereMesh = new Mesh(vertices, indices);
    setNormalsSphere(SphereMesh);
    return SphereMesh;
}

void        Structures::Mesh::setNormalsSphere(Mesh* SphereMesh) // calculate the average face normal for each vertex
{
    LibMath::Vector3    v1;
    LibMath::Vector3    v2;
    LibMath::Vector3    v3;
    LibMath::Vector3    v1v2;
    LibMath::Vector3    v1v3;
    LibMath::Vector3    normal;

    for (int i = 0; i < SphereMesh->m_indices.size(); i += 3)
    {
        v1 = SphereMesh->m_vertices[SphereMesh->m_indices[i]].m_position;
        v2 = SphereMesh->m_vertices[SphereMesh->m_indices[i + 1]].m_position;
        v3 = SphereMesh->m_vertices[SphereMesh->m_indices[i + 2]].m_position;

        v1v2 = v2 - v1;
        v1v3 = v3 - v1;

        normal = v1v2.cross(v1v3); // calculate the face normal

        SphereMesh->m_vertices[SphereMesh->m_indices[i]].m_normal += normal; // add it to the on of the other face
        SphereMesh->m_vertices[SphereMesh->m_indices[i + 1]].m_normal += normal; // of the vertex to get the average
        SphereMesh->m_vertices[SphereMesh->m_indices[i + 2]].m_normal += normal;
    }
}
