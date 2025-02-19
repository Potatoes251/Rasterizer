#include "entity.h"

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

Structures::Entity& Structures::Entity::operator=(Entity const& other)
{
    m_mesh = other.m_mesh;

    m_transform = other.m_transform;

    return *this;
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

        Structures::Vertex result(temp, vertex.m_color);
        result.m_normal = vertex.m_normal;

        transformed.m_vertices.push_back(result);
    }

    return transformed;
}