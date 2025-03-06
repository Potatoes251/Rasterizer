#define _USE_MATH_DEFINES
#include "rasterizer.h"

void Structures::Rasterizer::renderScene(Scene* pScene, Texture* pTexture, const LibMath::Matrix4& projectionMatrix, LibMath::Matrix4 const& viewMatrix, bool wireframe)
{// render the scene in the texture

    pTexture->clearTexture();   // reset the texture
    Mesh transformedMesh;
    //Structures::Vertex viewPoint(0, 0, 1);
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
            
            // Clip the triangle against the NDC frustum
            std::vector<std::vector<Vertex>> Triangles = clipToPlanes(transformedMesh.m_vertices[index1],
                                                                        transformedMesh.m_vertices[index2],
                                                                        transformedMesh.m_vertices[index3]);
            //std::vector<Vertex> clippedTriangle = triangle;

            //std::cout << "After clipping : " << Triangles.size() << std::endl;

            for each(std::vector<Vertex> clippedTriangle in Triangles)
            {
                // project vertex on a 2D plane
                Vertex v1 = projectVertex(clippedTriangle[0], pTexture->m_width, pTexture->m_height);
                Vertex v2 = projectVertex(clippedTriangle[1], pTexture->m_width, pTexture->m_height);
                Vertex v3 = projectVertex(clippedTriangle[2], pTexture->m_width, pTexture->m_height);

                if (edgeFunction(v1, v2, v3) < 0) continue; // back face culling

                if (wireframe)
                {   // draw in wireframe
                    drawLine(v1, v2, *pTexture);
                    drawLine(v2, v3, *pTexture);
                    drawLine(v1, v3, *pTexture);
                }
                else // draw full triangle
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

Structures::Color Structures::Rasterizer::getTexelColor(Vertex v, Texture* tex)
{// bilinear interpolation

    float   xTex = v.m_u * (tex->m_width - 1);
    float   yTex = v.m_v * (tex->m_height - 1);

    int     xMin = static_cast<int>(xTex);
    int     yMin = static_cast<int>(yTex);
    int     xMax = static_cast<int>(xTex) + 1;
    int     yMax = static_cast<int>(yTex) + 1;

    Structures::Color   colorBL = tex->m_pixels[(yMin * tex->m_width) + xMin];  // fetch color of nearby pixel
    Structures::Color   colorBR = tex->m_pixels[(yMin * tex->m_width) + xMax];
    Structures::Color   colorTL = tex->m_pixels[(yMax * tex->m_width) + xMin];
    Structures::Color   colorTR = tex->m_pixels[(yMax * tex->m_width) + xMax];

    Structures::Color   colorBottom = colorBL * (xMax - xTex) + colorBR * (xTex - xMin);    // interpolate bottom line
    Structures::Color   colorTop = colorTL * (xMax - xTex) + colorTR * (xTex - xMin);       // interpolate top line

    return colorBottom * (yMax - yTex) + colorTop * (yTex - yMin);  // interpolate between top and bottom
}

void Structures::Rasterizer::fillTriangle(Vertex v1, Vertex v2, Vertex v3, Texture& sceneTexture, Texture* objectTexture, float alphaEntity, std::vector<Structures::Light> lights)
{
    float area = edgeFunction(v1, v2, v3);

    int xMin = std::min(std::min(v1[0], v2[0]), v3[0]); // set the bounding box of the triangle
    int xMax = std::max(std::max(v1[0], v2[0]), v3[0]); // to only go through the pixel inside it

    int yMin = std::min(std::min(v1[1], v2[1]), v3[1]);
    int yMax = std::max(std::max(v1[1], v2[1]), v3[1]);

    float zMax = (v1[2] > v2[2]) ? v1[2] : v2[2];   // take the zMax for the zbuffer
    zMax = (v3[2] > zMax) ? v3[2] : zMax;

    Structures::Vertex point;

    for (int i = xMin; i < xMax; i++)
    {
        for (int j = yMin; j < yMax; j++)
        {
            point = Structures::Vertex(i, j, 0);    // create a temp vertex to store info about the current pixel

            float alpha = edgeFunction(v1, v2, point) / area;   // calculate barycentric coordinate
            float beta = edgeFunction(v2, v3, point) / area;
            float gamma = edgeFunction(v3, v1, point) / area;
            if (alpha < 0 || beta < 0 || gamma < 0 || alpha + beta + gamma - 1 >= 0.0005) continue;
            
            point.m_normal = (v3.m_normal * alpha + v1.m_normal * beta + v2.m_normal * gamma);
            point.m_normal.normalize(); // interpolate the normal
            
            if (objectTexture)
            {
                point.m_u = (v3.m_u * alpha + v1.m_u * beta + v2.m_u * gamma);  // interpolate the texture coordinate
                point.m_v = (v3.m_v * alpha + v1.m_v * beta + v2.m_v * gamma);

                point.m_color = getTexelColor(point, objectTexture); // fetch texel color
            }
            else
            {
                point.m_color = Structures::Color(v3.m_color * alpha + v1.m_color * beta + v2.m_color * gamma);
                point.m_color.m_a = 255;    // interpolate color when there is no texture on the cube
            }
            for (int k = 0; k < lights.size(); ++k)
            {   // apply lighting of all light source on the point
                point.calculateLighting(lights[k], Structures::Vertex(0, 0, 1));
            }
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
    LibMath::Vector3 yaxis = xaxis.cross(zaxis); // Already normalized

    float dotXAxis = xaxis.dot(eye);
    float dotYAxis = yaxis.dot(eye);
    float dotZAxis = zaxis.dot(eye);


    LibMath::Matrix4 ViewMatrix(
        xaxis.getX(), yaxis.getX(), zaxis.getX(), -dotXAxis,
        xaxis.getY(), yaxis.getY(), zaxis.getY(), -dotYAxis,
        xaxis.getZ(), yaxis.getZ(), zaxis.getZ(), -dotZAxis,
            0.f,          0.f,          0.f,          1
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

void Structures::inputManager(Structures::Camera& camera, bool& wireframe)
{
    if (IsKeyPressed(KEY_F1))
    {
        wireframe = !wireframe;
    }
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

void Structures::mainLoop(Structures::Camera& camera, Texture& texture, Scene& scene, LibMath::Matrix4& projectionMatrix)
{
    // execute the main loop
    Structures::Rasterizer  rasterizer;
    float                   rotation = 0.f;
    bool                    wireframe = false;

    while (!WindowShouldClose())
    {
        Structures::inputManager(camera, wireframe);

        LibMath::Matrix4 viewMatrix = Structures::createViewMatrix(camera.m_position, camera.m_pitch, camera.m_yaw);

        rotation += 0.05f;
        scene.m_entities[0].m_transform = LibMath::Matrix4::createTransform(LibMath::Vector3(0.f, -2.f, -2.f),
            LibMath::Radian(rotation),
            LibMath::Vector3(1.5f, 1.5f, 1.5f));
        scene.m_entities[2].m_transform = LibMath::Matrix4::createTransform(LibMath::Vector3(2.f, 0.f, -2.f),
            LibMath::Radian(rotation));
        scene.m_entities[3].m_transform = LibMath::Matrix4::createTransform(LibMath::Vector3(0.f, 1.5f, -3.f),
            LibMath::Radian(rotation),
            LibMath::Vector3(1.25f, 1.25f, 1.25f));
        scene.m_entities[4].m_transform = LibMath::Matrix4::createTransform(LibMath::Vector3(0.f, 0.5f, -0.0f),
            LibMath::Radian(rotation));
        scene.m_entities[5].m_transform = LibMath::Matrix4::createTransform(LibMath::Vector3(-2.f, 0.f, -2.f),
            LibMath::Radian(rotation));

        // render the scene in the texture
        rasterizer.renderScene(&scene, &texture, projectionMatrix, viewMatrix, wireframe);

        texture.drawTexture(); // Draw the rasterized scene
    }
}

void Structures::deleteAndCloseWindow(Scene& scene)
{
    for (int i = 0; i < scene.m_entities.size(); ++i)
    {
        if (scene.m_entities[i].m_texture)
        {
            delete scene.m_entities[i].m_texture;
        }
        if (scene.m_entities[i].m_mesh)
        {
            delete scene.m_entities[i].m_mesh;
        }
    }

    CloseWindow();
}

Structures::Vertex Structures::Rasterizer::projectVertex(Vertex v, float width, float height)
{// project vertex on a 2D plane
    float x = v.m_position.getX();
    float y = v.m_position.getY();
    int p_x = ((x / 1.005) + 1) * 0.5 * width;
    int p_y = height - (((y / 1.005) + 1) * 0.5 * height);

    Structures::Vertex projectedVertex(p_x, p_y, v[2], v.m_color);
    projectedVertex.m_normal = v.m_normal;
    projectedVertex.m_u = v.m_u;
    projectedVertex.m_v = v.m_v;

    return projectedVertex;
}
