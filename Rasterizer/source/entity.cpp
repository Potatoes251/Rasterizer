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
        temp = LibMath::Vector4(vertex.m_position, 1.0f);   // transform the position
        temp = m_transform * temp;
        temp.homogenize();

        Structures::Vertex result(temp, vertex.m_color);

        temp = LibMath::Vector4(vertex.m_normal, 1.0f);     // transform the normal
        temp = m_transform * temp;
        temp.homogenize();

        result.m_normal = LibMath::Vector3 (temp.getX(), temp.getY(), temp.getZ());

        transformed.m_vertices.push_back(result);
    }

    return transformed;
}