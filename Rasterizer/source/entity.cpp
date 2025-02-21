#include "entity.h"

Structures::Entity::Entity(Mesh* mesh, LibMath::Matrix4 transform, Texture* tex)
{
    m_mesh = mesh;

    m_transform = transform;

    m_texture = tex;
}

Structures::Entity::Entity(Entity const& other)
{
    m_mesh = other.m_mesh;

    m_transform = other.m_transform;

    m_texture = other.m_texture;
}

Structures::Entity& Structures::Entity::operator=(Entity const& other)
{
    m_mesh = other.m_mesh;

    m_transform = other.m_transform;

    m_texture = other.m_texture;

    return *this;
}

Structures::Mesh Structures::Entity::getTransformedMesh(void)
{
    Mesh transformed;
    LibMath::Vector4 temp;

    transformed.m_indices = m_mesh->m_indices;

    LibMath::Matrix4 transposeTransformMatrix = m_transform.inverse().transpose();

    for each(Structures::Vertex vertex in m_mesh->m_vertices)
    {
        temp = LibMath::Vector4(vertex.m_position, 1.0f);   // transform the position
        temp = m_transform * temp;
        temp.homogenize();

        Structures::Vertex result(temp, vertex.m_color);

        temp = LibMath::Vector4(vertex.m_normal, 1.0f);     // transform the normal
        temp = transposeTransformMatrix * temp;
        temp.homogenize();

        result.m_normal = LibMath::Vector3 (temp.getX(), temp.getY(), temp.getZ());
        result.m_u = vertex.m_u;
        result.m_v = vertex.m_v;

        transformed.m_vertices.push_back(result);
    }

    return transformed;
}