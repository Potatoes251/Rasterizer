#include "mesh.h"

Structures::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<int> indices)
{
    m_vertices = vertices;
    m_indices = indices;
}

Structures::Mesh::Mesh() {}

Structures::Mesh* Structures::Mesh::createCube(Texture* tex)
{
    Mesh* cubeMesh = new Mesh();

    cubeMesh->pTexture = tex;

    // Define the vertices of the cube with texture coordinates
    static const Vertex coordinates[] = {
        // Back face
        { +0.5, +0.5, -0.5, 1.0f, 1.0f, COLOR_GOLD}, // Top-right
        {-0.5, +0.5, -0.5, 0.0f, 1.0f, COLOR_GOLD}, // Top-left
        {+0.5, -0.5, -0.5, 1.0f, 0.0f, COLOR_GOLD}, // Bottom-right
        {-0.5, -0.5, -0.5, 0.0f, 0.0f, COLOR_GOLD}, // Bottom-left

        // Front face
        {-0.5, -0.5, +0.5, 0.0f, 0.0f, COLOR_GOLD}, // Bottom-left
        {-0.5, +0.5, +0.5, 0.0f, 1.0f, COLOR_GOLD}, // Top-left
        {+0.5, +0.5, +0.5, 1.0f, 1.0f, COLOR_GOLD}, // Top-right
        {+0.5, -0.5, +0.5, 1.0f, 0.0f, COLOR_GOLD}, // Bottom-right

        // Left face
        {-0.5, +0.5, -0.5, 1.0f, 1.0f, COLOR_GOLD}, // Top-right
        {-0.5, +0.5, +0.5, 0.0f, 1.0f, COLOR_GOLD}, // Top-left
        {-0.5, -0.5, -0.5, 1.0f, 0.0f, COLOR_GOLD}, // Bottom-right
        {-0.5, -0.5, +0.5, 0.0f, 0.0f, COLOR_GOLD}, // Bottom-left

        // Right face
        {+0.5, +0.5, -0.5, 0.0f, 1.0f, COLOR_GOLD}, // Top-right
        {+0.5, +0.5, +0.5, 1.0f, 1.0f, COLOR_GOLD}, // Top-left
        {+0.5, -0.5, -0.5, 0.0f, 0.0f, COLOR_GOLD}, // Bottom-right
        {+0.5, -0.5, +0.5, 1.0f, 0.0f, COLOR_GOLD}, // Bottom-left

        // Top face
        {+0.5, +0.5, +0.5, 0.0f, 1.0f, COLOR_GOLD}, // Top-right
        {-0.5, +0.5, +0.5, 1.0f, 1.0f, COLOR_GOLD}, // Top-left
        {+0.5, +0.5, -0.5, 0.0f, 0.0f, COLOR_GOLD}, // Bottom-right
        {-0.5, +0.5, -0.5, 1.0f, 0.0f, COLOR_GOLD}, // Bottom-left

        // Bottom face
        {+0.5, -0.5, -0.5, 0.0f, 1.0f, COLOR_GOLD}, // Top-right
        {-0.5, -0.5, -0.5, 1.0f, 1.0f, COLOR_GOLD}, // Top-left
        {+0.5, -0.5, +0.5, 0.0f, 0.0f, COLOR_GOLD}, // Bottom-right
        {-0.5, -0.5, +0.5, 1.0f, 0.0f, COLOR_GOLD}, // Bottom-left
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

    setCubeNormals(cubeMesh);

    return cubeMesh;
}

void Structures::Mesh::setCubeNormals(Mesh* cubeMesh)
{
    // Calculate the normals for each vertex
    Vertex v1, v2, v3;
    LibMath::Vector3 v1v2;
    LibMath::Vector3 v1v3;
    LibMath::Vector3 normal;
    std::vector<LibMath::Vector3> vertexNormals(cubeMesh->m_vertices.size(), LibMath::Vector3(0.0f, 0.0f, 0.0f));

    for (int i = 0; i < cubeMesh->m_indices.size(); i += 3)
    {
        v1 = cubeMesh->m_vertices[cubeMesh->m_indices[i]];
        v2 = cubeMesh->m_vertices[cubeMesh->m_indices[i + 1]];
        v3 = cubeMesh->m_vertices[cubeMesh->m_indices[i + 2]];

        v1v3 = v3.m_position - v1.m_position;
        v1v2 = v2.m_position - v1.m_position;

        normal = v1v2.cross(v1v3);

        vertexNormals[cubeMesh->m_indices[i]] += normal;
        vertexNormals[cubeMesh->m_indices[i + 1]] += normal;
        vertexNormals[cubeMesh->m_indices[i + 2]] += normal;

    }

    // adds together the normals of the sames vertices
    std::vector<std::vector<size_t>> sameVertexGroups = {
        {0, 12, 18},
        {1, 8, 19},
        {2, 14, 20},
        {3, 10, 21},
        {4, 11, 23},
        {5, 9, 17},
        {6, 13, 16},
        {7, 15, 22}
    };

    for (const auto& group : sameVertexGroups)
    {
        LibMath::Vector3 averageNormal(0.0f, 0.0f, 0.0f);
        for (size_t idx : group)
        {
            averageNormal += vertexNormals[idx];
        }
        for (size_t idx : group)
        {
            cubeMesh->m_vertices[idx].m_normal = averageNormal;
        }
    }

    // Normalize the normals
    for (int i = 0; i < cubeMesh->m_vertices.size(); i++)
    {
        cubeMesh->m_vertices[i].m_normal.normalize();
    }
}




Structures::Mesh* Structures::Mesh::createCube()
{
    Mesh* cubeMesh = new Mesh();

    static const Vertex coordinates[] = {
    { +0.5, +0.5, -0.5, COLOR_GOLD}, // Back-top-right
    {-0.5, +0.5, -0.5, COLOR_GOLD}, // Back-top-left
    {+0.5, -0.5, -0.5, COLOR_GOLD}, // Back-bottom-right
    {-0.5, -0.5, -0.5, COLOR_GOLD}, // Back-bottom-left
    {-0.5, -0.5, +0.5, COLOR_GOLD}, // Front-bottom-left
    {-0.5, +0.5, +0.5, COLOR_GOLD}, // Front-top-left
    {+0.5, +0.5, +0.5, COLOR_GOLD}, // Front-top-right
    {+0.5, -0.5, +0.5, COLOR_GOLD}, // Front-bottom-right
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

    Vertex v1, v2, v3;

    LibMath::Vector3 v1v2;
    LibMath::Vector3 v1v3;
    LibMath::Vector3 normal;

    for (size_t i = 0; i < cubeMesh->m_indices.size(); i += 3)
    {
        v1 = cubeMesh->m_vertices[cubeMesh->m_indices[i]];
        v2 = cubeMesh->m_vertices[cubeMesh->m_indices[i + 1]];
        v3 = cubeMesh->m_vertices[cubeMesh->m_indices[i + 2]];

        v1v3 = v3.m_position - v1.m_position;
        v1v2 = v2.m_position - v1.m_position;

        normal = v1v2.cross(v1v3);

        cubeMesh->m_vertices[cubeMesh->m_indices[i]].m_normal += normal;
        cubeMesh->m_vertices[cubeMesh->m_indices[i + 1]].m_normal += normal;
        cubeMesh->m_vertices[cubeMesh->m_indices[i + 2]].m_normal += normal;
    }

    for (size_t i = 0; i < cubeMesh->m_vertices.size(); i++)
    {
        cubeMesh->m_vertices[i].m_normal.normalize();
    }

    return cubeMesh;
}






