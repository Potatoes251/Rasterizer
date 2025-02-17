#include "structures.h"

Structures::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<int> indices)
{
    m_vertices = vertices;

    m_indices = indices;
}

Structures::Mesh::Mesh()
{
}

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

Structures::Vertex::Vertex(float x, float y, float z)
{
	m_position = LibMath::Vector3(x, y, z);
}

Structures::Vertex::Vertex(LibMath::Vector4 vec)
{
    m_position = LibMath::Vector3(vec.getX(), vec.getY(), vec.getZ());
}

Structures::Vertex::Vertex(LibMath::Vector3 vec)
{
    m_position = vec;
}

Structures::Texture::Texture(unsigned int width, unsigned int height, Color color)
{
    m_width = width;

    m_height = height;

    m_pixels = new Color[width * height];

    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            m_pixels[(j * width) + i] = color;
        }
    }
}

void Structures::Texture::setPixelColor(unsigned int x, unsigned int y, const Color& c)
{
    m_pixels[(y * m_width) + x] = c;
}

Structures::Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    m_r = r;
    m_g = g; 
    m_b = b; 
    m_a = a;
}

Structures::Entity::Entity(Mesh* mesh, LibMath::Matrix4 transform)
{
    m_mesh = mesh;

    m_transform = transform;
}

Structures::Entity::Entity(Entity const& other)
{
    m_mesh = other.m_mesh;

    m_transform = other.m_transform;
}

Structures::Mesh Structures::Entity::getTransformedMesh(void)
{
    Mesh transformed;
    LibMath::Vector4 temp;

    transformed.m_indices = m_mesh->m_indices;

    for each(Structures::Vertex vertex in m_mesh->m_vertices)
    {
        temp = LibMath::Vector4(vertex.m_position, 1.0f);

        temp = m_transform * temp;

        temp.homogenize();

        transformed.m_vertices.push_back(Structures::Vertex(temp));
    }

    return transformed;
}

void Structures::Rasterizer::renderScene(Scene* pScene, Texture* pTexture)
{

    Mesh transformedMesh;

    for each(Entity entity in pScene->m_entities)
    {
        transformedMesh = entity.getTransformedMesh();

        for (size_t i = 0; i < transformedMesh.m_indices.size(); i += 3)
        {
            int index1 = transformedMesh.m_indices[i];
            float x1 = transformedMesh.m_vertices[index1].m_position.getX();
            float y1 = transformedMesh.m_vertices[index1].m_position.getY();
            int p_x1 = ((x1 / 5) + 1) * 0.5 * pTexture->m_width;
            int p_y1 = pTexture->m_height - (((y1 / 5) + 1) * 0.5 * pTexture->m_height);

            int index2 = transformedMesh.m_indices[i + 1];
            float x2 = transformedMesh.m_vertices[index2].m_position.getX();
            float y2 = transformedMesh.m_vertices[index2].m_position.getY();
            int p_x2 = ((x2 / 5) + 1) * 0.5 * pTexture->m_width;
            int p_y2 = pTexture->m_height - (((y2 / 5) + 1) * 0.5 * pTexture->m_height);
            
            int index3 = transformedMesh.m_indices[i + 2];
            float x3 = transformedMesh.m_vertices[index3].m_position.getX();
            float y3 = transformedMesh.m_vertices[index3].m_position.getY();
            int p_x3 = ((x3 / 5) + 1) * 0.5 * pTexture->m_width;
            int p_y3 = pTexture->m_height - (((y3 / 5) + 1) * 0.5 * pTexture->m_height);

            drawLine(p_x1, p_y1, p_x2, p_y2, *pTexture);
            drawLine(p_x2, p_y2, p_x3, p_y3, *pTexture);
            drawLine(p_x1, p_y1, p_x3, p_y3, *pTexture);
        }
    }
    
}

void Structures::drawLine(int x0, int y0, int x1, int y1, Structures::Texture& tex) {
    // Calculate the differences in x and y
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    // Determine the direction of the line
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    // Initialize the error term
    int err = dx - dy;

    // Vector to store the points of the line
    std::vector<std::pair<int, int>> linePoints;

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

Structures::Scene::Scene(std::vector<Entity> entities)
{
    m_entities = entities;
}
