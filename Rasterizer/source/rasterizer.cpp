#include "rasterizer.h"

void Structures::Rasterizer::renderScene(Scene* pScene, Texture* pTexture, bool wireframe)
{
    pTexture->clearTexture();
    Mesh transformedMesh;
    Structures::Vertex viewPoint(0, 0, 1);

    for (int j = 0; j < pScene->m_entities.size(); j++)
    {
        transformedMesh = pScene->m_entities[j].getTransformedMesh();

        for (size_t i = 0; i < transformedMesh.m_indices.size(); i += 3)
        {
            int index1 = transformedMesh.m_indices[i];

            int index2 = transformedMesh.m_indices[i + 1];

            int index3 = transformedMesh.m_indices[i + 2];

            if (wireframe)
            {
                drawLine(projectVertex(transformedMesh.m_vertices[index1], pTexture->m_width, pTexture->m_height), 
                 projectVertex(transformedMesh.m_vertices[index2], pTexture->m_width, pTexture->m_height), 
                 *pTexture);
                drawLine(projectVertex(transformedMesh.m_vertices[index2], pTexture->m_width, pTexture->m_height), 
                 projectVertex(transformedMesh.m_vertices[index3], pTexture->m_width, pTexture->m_height), 
                 *pTexture);
                drawLine(projectVertex(transformedMesh.m_vertices[index1], pTexture->m_width, pTexture->m_height), 
                 projectVertex(transformedMesh.m_vertices[index3], pTexture->m_width, pTexture->m_height), 
                 *pTexture);
            }

            else
                fillTriangle(
                    projectVertex(transformedMesh.m_vertices[index1], pTexture->m_width, pTexture->m_height),
                    projectVertex(transformedMesh.m_vertices[index2], pTexture->m_width, pTexture->m_height),
                    projectVertex(transformedMesh.m_vertices[index3], pTexture->m_width, pTexture->m_height), 
                    *pTexture, pScene->m_entities[j].m_mesh->pTexture);
        }
    }
}

float Structures::Rasterizer::edgeFunction(Vertex v1, Vertex v2, Vertex v3)
{
    return -((v2[0] - v1[0]) * (v3[1] - v1[1]) - (v2[1] - v1[1]) * (v3[0] - v1[0]));
}

Structures::Color Structures::Rasterizer::getNearestTexel(Vertex v, Texture* tex)
{
    float xTex = v.m_u * tex->m_width;
    float yTex = v.m_v * tex->m_height;

    int x = static_cast<int>(xTex);
    int y = static_cast<int>(yTex);

    if (xTex - x >= 0.5f)
    {
        ++x;
    }
    if (yTex - y >= 0.5f)
    {
        ++y;
    }
    Structures::Color c = tex->m_pixels[(y * tex->m_width) + x];
    return c;
}

Structures::Color Structures::Rasterizer::getTexelColor(Vertex v, Texture* tex)
{
    float xTex = v.m_u * (tex->m_width-1);
    float yTex = v.m_v * (tex->m_height - 1);

    int xMin = static_cast<int>(xTex);
    int yMin = static_cast<int>(yTex);
    int xMax = static_cast<int>(xTex) + 1;
    int yMax = static_cast<int>(yTex) + 1;

    Structures::Color colorBL = tex->m_pixels[(yMin * tex->m_width) + xMin];
    Structures::Color colorBR = tex->m_pixels[(yMin * tex->m_width) + xMax];
    Structures::Color colorTL = tex->m_pixels[(yMax * tex->m_width) + xMin];
    Structures::Color colorTR = tex->m_pixels[(yMax * tex->m_width) + xMax];

    Structures::Color colorBottom = colorBL * (xMax - xTex) + colorBR * (xTex - xMin);// interpolate bottom line
    Structures::Color colorTop = colorTL * (xMax - xTex) + colorTR * (xTex - xMin);// interpolate top line

    return colorBottom * (yMax - yTex) + colorTop * (yTex - yMin);
}

void Structures::Rasterizer::fillTriangle(Vertex v1, Vertex v2, Vertex v3, Texture& sceneTexture, Texture* objectTexture)
{
    float area = edgeFunction(v1, v2, v3);

    if (area < 0) return;

    int xMin = std::min(std::min(v1[0], v2[0]), v3[0]);
    int xMax = std::max(std::max(v1[0], v2[0]), v3[0]);

    int yMin = std::min(std::min(v1[1], v2[1]), v3[1]);
    int yMax = std::max(std::max(v1[1], v2[1]), v3[1]);;

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
            
            point.m_normal = LibMath::Vector3(v3.m_normal * alpha + v1.m_normal * beta + v2.m_normal * gamma);
            point.m_normal.normalize();
            if (objectTexture != nullptr)
            {
                point.m_u = (v3.m_u * alpha + v1.m_u * beta + v2.m_u * gamma);
                point.m_v = (v3.m_v * alpha + v1.m_v * beta + v2.m_v * gamma);

                point.m_color = getTexelColor(point, objectTexture);
            }
            else
            {
                point.m_color = Structures::Color(v3.m_color * alpha + v1.m_color * beta + v2.m_color * gamma);
            }
            point.calculateLighting(Structures::Light(0.2, 0.4, 0.4, LibMath::Vector3::zero()), Structures::Vertex(0, 0, 1));
            sceneTexture.setPixelColor(i, j, point.m_color);
        }
    }
}

void Structures::Rasterizer::drawLine(Vertex v0, Vertex v1, Structures::Texture& tex)
{
    int x0 = v0[0];
    int y0 = v0[1];
    int x1 = v1[0];
    int y1 = v1[1];

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

Structures::Vertex Structures::Rasterizer::projectVertex(Vertex v, float width, float height)
{
    float x = v.m_position.getX();
    float y = v.m_position.getY();
    int p_x = ((x / 5) + 1) * 0.5 * width;
    int p_y = height - (((y / 5) + 1) * 0.5 * height);

    Structures::Vertex projectedVertex(p_x, p_y, 0, v.m_color);
    projectedVertex.m_normal = v.m_normal;
    projectedVertex.m_u = v.m_u;
    projectedVertex.m_v = v.m_v;

    return projectedVertex;
}
