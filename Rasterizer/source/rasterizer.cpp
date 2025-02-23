#define _USE_MATH_DEFINES
#include "rasterizer.h"

void Structures::Rasterizer::renderScene(Scene* pScene, Texture* pTexture, const LibMath::Matrix4& projectionMatrix, LibMath::Matrix4 const& viewMatrix, bool wireframe)
{

    Mesh transformedMesh;

    for each(Entity entity in pScene->m_entities)
    {
        transformedMesh = entity.getTransformedMesh();

        transformedMesh = Structures::Entity::getCameraProjectedMesh(transformedMesh, viewMatrix);

        transformedMesh = Structures::Entity::getProjectedMesh(transformedMesh, projectionMatrix);

        for (size_t i = 0; i < transformedMesh.m_indices.size(); i += 3)
        {
            int index1 = transformedMesh.m_indices[i];
            int index2 = transformedMesh.m_indices[i + 1];
            int index3 = transformedMesh.m_indices[i + 2];

            std::vector<Vertex> triangle = {
            Vertex(transformedMesh.m_vertices[index1].m_position, transformedMesh.m_vertices[index1].m_color),
            Vertex(transformedMesh.m_vertices[index2].m_position, transformedMesh.m_vertices[index2].m_color),
            Vertex(transformedMesh.m_vertices[index3].m_position, transformedMesh.m_vertices[index3].m_color)
            };

            std::vector<Vertex> triangle2 = {
  
            Vertex({ +0.5, +0.5, -2.5}, transformedMesh.m_vertices[index1].m_color),
            Vertex({-0.5, +0.5, -0.5}, transformedMesh.m_vertices[index2].m_color),
            Vertex({+0.5, -0.5, -0.5}, transformedMesh.m_vertices[index3].m_color),
//            Vertex({-0.5, -0.5, -0.5}, transformedMesh.m_vertices[index3].m_color)
            };

            std::cout << "Before Clipping: " << triangle.size() << " vertices\n";
            for (auto& v : triangle) {
                std::cout << "(" << v.m_position.getX() << ", " << v.m_position.getY() << ", " << v.m_position.getZ() << ")\n";
            }
            // Clip the triangle against the NDC frustum
            //std::vector<Vertex> clippedTriangle = clipToPlanes(triangle);
            std::vector<Vertex> clippedTriangle = triangle;

            std::cout << "After Clipping: " << clippedTriangle.size() << " vertices\n";

            
            
            if (!clippedTriangle.empty())
            {
                float x1 = clippedTriangle[0].m_position.getX();
                float y1 = clippedTriangle[0].m_position.getY();
                int p_x1 = ((x1 / 5) + 1) * 0.5 * pTexture->m_width;
                int p_y1 = pTexture->m_height - (((y1 / 5) + 1) * 0.5 * pTexture->m_height);
                float p_z1 = clippedTriangle[0].m_position.getZ();


                float x2 = clippedTriangle[1].m_position.getX();
                float y2 = clippedTriangle[1].m_position.getY();
                int p_x2 = ((x2 / 5) + 1) * 0.5 * pTexture->m_width;
                int p_y2 = pTexture->m_height - (((y2 / 5) + 1) * 0.5 * pTexture->m_height);
                float p_z2 = clippedTriangle[1].m_position.getZ();


                float x3 = clippedTriangle[2].m_position.getX();
                float y3 = clippedTriangle[2].m_position.getY();
                int p_x3 = ((x3 / 5) + 1) * 0.5 * pTexture->m_width;
                int p_y3 = pTexture->m_height - (((y3 / 5) + 1) * 0.5 * pTexture->m_height);
                float p_z3 = clippedTriangle[2].m_position.getZ();

                std::cout << "x1: " << x1 << " y1 : " << y1 << " z1: " << p_z1 << '\n';
                std::cout << "p_x1: " << p_x1 << " p_y1 : " << p_y1 << " p_z1: " << p_z1 << '\n';

                if (wireframe)
                {
                    drawLine(p_x1, p_y1, p_x2, p_y2, *pTexture);
                    drawLine(p_x2, p_y2, p_x3, p_y3, *pTexture);
                    drawLine(p_x1, p_y1, p_x3, p_y3, *pTexture);
                }
                else
                {
                    fillTriangle(Structures::Vertex(p_x1, p_y1, p_z1, clippedTriangle[0].m_color),
                        Structures::Vertex(p_x2, p_y2, p_z2, clippedTriangle[1].m_color),
                        Structures::Vertex(p_x3, p_y3, p_z3, clippedTriangle[2].m_color), *pTexture);
                }
            }
                
        }
    }
}

float Structures::Rasterizer::edgeFunction(Vertex v1, Vertex v2, Vertex v3)
{
    return -((v2[0] - v1[0]) * (v3[1] - v1[1]) - (v2[1] - v1[1]) * (v3[0] - v1[0]));
}

void Structures::Rasterizer::fillTriangle(Vertex v1, Vertex v2, Vertex v3, Texture& tex)
{
    float area = edgeFunction(v1, v2, v3);

    if (area < 0) return;

    int xMin = (v1[0] < v2[0]) ? v1[0] : v2[0];
    xMin = (v3[0] < xMin) ? v3[0] : xMin;

    int xMax = (v1[0] > v2[0]) ? v1[0] : v2[0];
    xMax = (v3[0] > xMax) ? v3[0] : xMax;

    int yMin = (v1[1] < v2[1]) ? v1[1] : v2[1];
    yMin = (v3[1] < yMin) ? v3[1] : yMin;

    int yMax = (v1[1] > v2[1]) ? v1[1] : v2[1];
    yMax = (v3[1] > yMax) ? v3[1] : yMax;

    float zMax = (v1[2] > v2[2]) ? v1[2] : v2[2];
    zMax = (v3[2] > zMax) ? v3[2] : zMax;

    Structures::Vertex point;

    for (int i = xMin; i < xMax; i++)
    {
        for (int j = yMin; j < yMax; j++)
        {
            point = Structures::Vertex(i, j, 0);

            float alpha = edgeFunction(v1, v2, point) / area;
            float beta = edgeFunction(v2, v3, point) / area;
            float gamma = edgeFunction(v3, v1, point) / area;
            if (alpha < 0 || beta < 0 || gamma < 0) continue;

            if (tex.buffer(i, j) < zMax) // z-culling
            {
                tex.setPixelColor(i, j, (v3.m_color * alpha + v1.m_color * beta + v2.m_color * gamma));
                tex.updateBuffer(i, j, zMax);
            }

            
        }
    }
}

void Structures::Rasterizer::drawLine(int x0, int y0, int x1, int y1, Structures::Texture& tex)
{
    // Calculate the differences in x and y
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    // Determine the direction of the line
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    // Initialize the error term
    int err = dx - dy;

    while (true) {
        // Add the current point to the vector
        tex.setPixelColor(x0, y0);

        // Check if we have reached the end point
        if (x0 == x1 && y0 == y1) {
            break;
        }

        // Calculate the next point
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

LibMath::Matrix4 Structures::createViewMatrix(const LibMath::Vector3 eye, float pitch, float yaw)
{
    // I assume the values are already converted to radians.
    float cosPitch = cos(pitch);
    float sinPitch = sin(pitch);
    float cosYaw = cos(yaw);
    float sinYaw = sin(yaw);

    LibMath::Vector3 xaxis = { cosYaw, 0, -sinYaw };
    LibMath::Vector3 yaxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
    LibMath::Vector3 zaxis = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

    float dotXAxis = xaxis.dot(eye);
    float dotYAxis = yaxis.dot(eye);
    float dotZaxis = zaxis.dot(eye);

    // Create a 4x4 view matrix from the right, up, forward and eye position vectors
    return LibMath::Matrix4(
        xaxis.getX(), yaxis.getX(), zaxis.getX(), 0,
        xaxis.getY(), yaxis.getY(), zaxis.getY(), 0,
        xaxis.getZ(), yaxis.getZ(), zaxis.getZ(), 0,
        -dotXAxis,    -dotYAxis,    -dotZaxis,    1 
    );
}

LibMath::Vector2 Structures::inputManager(void)
{
    float angleX = 0.f;
    float angleY = 0.f;
    return LibMath::Vector2();
}
