#include "entity.h"
#include "memoryLeak.h"


Structures::Entity::Entity(Mesh* mesh, LibMath::Matrix4 transform, Texture* tex, float alpha)
{
    m_mesh = mesh;
    m_transform = transform;
    m_texture = tex;
    m_alpha = alpha;
}

Structures::Entity::Entity(Entity const& other)
{
    m_mesh = other.m_mesh;
    m_transform = other.m_transform;
    m_texture = other.m_texture;
    m_alpha = other.m_alpha;
}

Structures::Entity&     Structures::Entity::operator=(Entity const& other)
{
    m_mesh = other.m_mesh;
    m_transform = other.m_transform;
    m_texture = other.m_texture;
    m_alpha = other.m_alpha;

    return *this;
}

Structures::Mesh    Structures::Entity::getTransformedMesh(LibMath::Matrix4 projection_viewMatrix)
{
    Mesh                transformed;
    LibMath::Vector4    temp;

    transformed.m_indices = m_mesh->m_indices;  // keep the same indices

    LibMath::Matrix4 transposeTransformMatrix = m_transform.inverse().transpose();  // for the normals

    for each(Structures::Vertex vertex in m_mesh->m_vertices)
    {
        temp = LibMath::Vector4(vertex.m_position, 1.0f);   // transform the position
        temp = projection_viewMatrix * (m_transform * temp);
        temp.homogenize();
        
        Structures::Vertex result(temp, vertex.m_color);
        
        temp = LibMath::Vector4(vertex.m_normal, 1.0f);     // transform the normal
        temp = transposeTransformMatrix * temp;

        result.m_normal = LibMath::Vector3 (temp.getX(), temp.getY(), temp.getZ());
        result.m_normal.normalize();    // normalize the normal

        result.m_u = vertex.m_u;    // keep the texture coordinate
        result.m_v = vertex.m_v;
        
        transformed.m_vertices.push_back(result);
        
    }

    return transformed;
}