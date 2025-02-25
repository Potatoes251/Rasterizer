#define _USE_MATH_DEFINES
#include "rasterizer.h"

void Structures::Rasterizer::renderScene(Scene* pScene, Texture* pTexture, const LibMath::Matrix4& projectionMatrix, LibMath::Matrix4 const& viewMatrix, bool wireframe)
{
    pTexture->clearTexture();
    Mesh transformedMesh;
    Structures::Vertex viewPoint(0, 0, 1);
	LibMath::Matrix4 projection_viewMatrix = projectionMatrix * viewMatrix;

    for each(Entity entity in pScene->m_entities)
    {
        transformedMesh = entity.getTransformedMesh(projection_viewMatrix);
        //transformedMesh = Structures::Entity::getProjectedMesh(transformedMesh, projectionMatrix, viewMatrix);

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

            /*std::cout << "Before Clipping: " << triangle.size() << " vertices\n";
            for (auto& v : triangle) {
                std::cout << "(" << v.m_position.getX() << ", " << v.m_position.getY() << ", " << v.m_position.getZ() << ")\n";
            }*/
            //// Clip the triangle against the NDC frustum
            std::vector<std::vector<Vertex>> Triangles = clipToPlanes(triangle);
            //std::vector<Vertex> clippedTriangle = triangle;

            //std::cout << "After clipping : " << Triangles.size() << std::endl;

            for each(std::vector<Vertex> clippedTriangle in Triangles)
            {
                Vertex v1 = projectVertex(clippedTriangle[0], pTexture->m_width, pTexture->m_height);
                Vertex v2 = projectVertex(clippedTriangle[1], pTexture->m_width, pTexture->m_height);
                Vertex v3 = projectVertex(clippedTriangle[2], pTexture->m_width, pTexture->m_height);

                if (edgeFunction(v1, v2, v3) < 0) continue;

                if (wireframe)
                {
                    drawLine(v1, v2, *pTexture);

                    drawLine(v2, v3, *pTexture);

                    drawLine(v1, v3, *pTexture);
                }
                else
                    fillTriangle(v1, v2, v3, *pTexture,
                        entity.m_mesh->m_texture, entity.m_alpha, pScene->m_lights);
            }
            
        }
    }
}

float Structures::Rasterizer::edgeFunction(Vertex v1, Vertex v2, Vertex v3)
{
    return -((v2[0] - v1[0]) * (v3[1] - v1[1]) - (v2[1] - v1[1]) * (v3[0] - v1[0]));
}

Structures::Color Structures::Rasterizer::getNearestTexel(Vertex v, Texture* tex)
{
    float xTex = v.m_u * (tex->m_width - 1);
    float yTex = v.m_v * (tex->m_height - 1);

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
{// bilinear interpolation
    float xTex = v.m_u * (tex->m_width - 1);
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

    return colorBottom * (yMax - yTex) + colorTop * (yTex - yMin);// interpolate between top and bottom
}

void Structures::Rasterizer::fillTriangle(Vertex v1, Vertex v2, Vertex v3, Texture& sceneTexture, Texture* objectTexture, float alphaEntity, std::vector<Structures::Light> lights)
{
    float area = edgeFunction(v1, v2, v3);

    if (area < 0) return;   // back face culling

    int xMin = std::max(0.f, std::min(std::min(v1[0], v2[0]), v3[0])); // set the bounding box of the triangle
    int xMax = std::min(static_cast<float>(sceneTexture.m_width), std::max(std::max(v1[0], v2[0]), v3[0]));

    int yMin = std::max(0.f, std::min(std::min(v1[1], v2[1]), v3[1]));
    int yMax = std::min(static_cast<float>(sceneTexture.m_height), std::max(std::max(v1[1], v2[1]), v3[1]));

    float zMax = (v1[2] > v2[2]) ? v1[2] : v2[2];
    zMax = (v3[2] > zMax) ? v3[2] : zMax;

    Structures::Vertex point;

    for (int i = xMin; i < xMax; i++)
    {
        for (int j = yMin; j < yMax; j++)
        {
            point = Structures::Vertex(i, j, 0);

            float alpha = edgeFunction(v1, v2, point) / area;   // barycentric coordinate
            float beta = edgeFunction(v2, v3, point) / area;
            float gamma = edgeFunction(v3, v1, point) / area;
            if (alpha < 0 || beta < 0 || gamma < 0 || alpha + beta + gamma - 1 >= 0.0005) continue;
            
            point.m_normal = v1.m_normal;
            point.m_normal.normalize();

            if (objectTexture)
            {
                point.m_u = (v3.m_u * alpha + v1.m_u * beta + v2.m_u * gamma);
                point.m_v = (v3.m_v * alpha + v1.m_v * beta + v2.m_v * gamma);

                //point.m_color = getNearestTexel(point, objectTexture);
                point.m_color = getTexelColor(point, objectTexture);
            }
            else
            {
                point.m_color = Structures::Color(v3.m_color * alpha + v1.m_color * beta + v2.m_color * gamma);
                point.m_color.m_a = 255;
            }
            for (int k = 0; k<lights.size(); ++k)
            point.calculateLighting(lights[k], Structures::Vertex(0, 0, 1));
            if (sceneTexture.buffer(i, j) < zMax) // z-culling
            {
                sceneTexture.setPixelColor(i, j, point.m_color, alphaEntity);
                sceneTexture.updateBuffer(i, j, zMax);
            }
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

    while (true) 
    {
        // Add the current point to the vector
        tex.setPixelColor(x0, y0);

        // Check if we have reached the end point
        if (x0 == x1 && y0 == y1) 
        {
            break;
        }

        // Calculate the next point
        int e2 = 2 * err;
        if (e2 > -dy) 
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) 
        {
            err += dx;
            y0 += sy;
        }
    }
}

LibMath::Matrix4 Structures::createViewMatrix(const LibMath::Vector3& eye, float pitch, float yaw)
{

    //std::cout << "In create view x: " << eye.getX() << " z: " << eye.getZ() << '\n';
    // I assume the values are already converted to radians.
    float cosPitch = LibMath::cos(LibMath::Radian(pitch));
    float sinPitch = LibMath::sin(LibMath::Radian(pitch));
    float cosYaw = LibMath::cos(LibMath::Radian(yaw));
    float sinYaw = LibMath::sin(LibMath::Radian(yaw)); 

    LibMath::Matrix4;

    // Forward vector (Z-axis, looking direction)
    LibMath::Vector3 zaxis = -LibMath::Vector3{
        cosPitch * sinYaw, // x
        -sinPitch,         // y
        cosPitch * cosYaw  // z
    };
    zaxis.normalize(); // Ensure it's a unit vector


    // Right vector (X-axis)
    LibMath::Vector3 xaxis = LibMath::Vector3(0.0f, 1.0f, 0.0f).cross(zaxis);
    xaxis.normalize();

    // Up vector (Y-axis)
    LibMath::Vector3 yaxis = zaxis.cross(xaxis); // Already normalized

    float dotXAxis = xaxis.dot(eye);
    float dotYAxis = yaxis.dot(eye);
    float dotZAxis = zaxis.dot(eye);


    LibMath::Matrix4 ViewMatrix(
        xaxis.getX(), yaxis.getX(), zaxis.getX(), dotXAxis,
        xaxis.getY(), yaxis.getY(), zaxis.getY(), dotYAxis,
        xaxis.getZ(), yaxis.getZ(), zaxis.getZ(), dotZAxis,
             0,            0,            0,           1
    );

    // Create a 4x4 view matrix from the right, up, forward and eye position vectors
    return ViewMatrix.inverse();
}

LibMath::Matrix4 Structures::lookAt(const LibMath::Vector3& eye, const LibMath::Vector3 target, LibMath::Vector3 up)
{

    LibMath::Vector3 zaxis = (eye - target);    // The "forward" vector.
    zaxis.normalize();

    LibMath::Vector3 xaxis = up.cross(zaxis);// The "right" vector.
    xaxis.normalize();

    LibMath::Vector3 yaxis = zaxis.cross(xaxis);     // The "up" vector.

    float dotXAxis = xaxis.dot(eye);
    float dotYAxis = yaxis.dot(eye);
    float dotZaxis = zaxis.dot(eye);

    // Create a 4x4 view matrix from the right, up, forward and eye position vectors
    LibMath::Matrix4 viewMatrix = {
        xaxis.getX(),            yaxis.getX(),            zaxis.getX(),       0,
        xaxis.getY(),            yaxis.getY(),            zaxis.getY(),       0,
        xaxis.getZ(),            yaxis.getZ(),            zaxis.getZ(),       0,
        dotXAxis,                dotYAxis,                dotZaxis,           1
    };
    return viewMatrix;
}

void Structures::inputManager(Structures::Camera& camera)
{
    float pitch = 0.f;
    float yaw = 0.f;
    float cameraPosZ = 0.f;
    float cameraPosX = 0.f;

    if (IsKeyPressed(KEY_UP))
    {
        camera.m_pitch -= 0.1f;
    }

    if (IsKeyPressed(KEY_DOWN))
    {
        camera.m_pitch += 0.1f;
    }

    if (IsKeyPressed(KEY_LEFT))
    {
        camera.m_yaw -= 0.1f;
    }

    if (IsKeyPressed(KEY_RIGHT))
    {
        camera.m_yaw += 0.1f;
    }

    float cameraSpeed = 0.2f;
    if (IsKeyPressed(KEY_W))
    {
        camera.m_position.getY() += cameraSpeed;
        //std::cout << "Camera z : " << camera.m_position.getZ() << '\n';
    }
    if (IsKeyPressed(KEY_S))
    {
        camera.m_position.getY() -= cameraSpeed;
        //std::cout << "Camera z : " << camera.m_position.getZ() << '\n';
    }
    if (IsKeyPressed(KEY_A))
    {
        camera.m_position.getX() += cameraSpeed; 
        //std::cout << "Camera x : " << camera.m_position.getX() << '\n';
    }
    if (IsKeyPressed(KEY_D))
    {
        camera.m_position.getX() -= cameraSpeed;
        //std::cout << "Camera x : " << camera.m_position.getX() << '\n';
    }

}

Structures::Vertex Structures::Rasterizer::projectVertex(Vertex v, float width, float height)
{// project vertex on a 2D plane
    float x = v.m_position.getX();
    float y = v.m_position.getY();
    int p_x = ((x / 1) + 1) * 0.5 * width;
    int p_y = height - (((y / 1) + 1) * 0.5 * height);

    Structures::Vertex projectedVertex(p_x, p_y, 0, v.m_color);
    projectedVertex.m_normal = v.m_normal;
    projectedVertex.m_u = v.m_u;
    projectedVertex.m_v = v.m_v;

    return projectedVertex;
}
