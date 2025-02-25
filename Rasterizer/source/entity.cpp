#include "entity.h"

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

Structures::Entity& Structures::Entity::operator=(Entity const& other)
{
    m_mesh = other.m_mesh;
    m_transform = other.m_transform;
    m_texture = other.m_texture;
    m_alpha = other.m_alpha;

    return *this;
}

Structures::Mesh Structures::Entity::getTransformedMesh(LibMath::Matrix4 projection_viewMatrix)
{
    Mesh transformed;
    LibMath::Vector4 temp;

    transformed.m_indices = m_mesh->m_indices;

    LibMath::Matrix4 transposeTransformMatrix = m_transform.inverse().transpose();

    for each(Structures::Vertex vertex in m_mesh->m_vertices)
    {
        temp = LibMath::Vector4(vertex.m_position, 1.0f);   // transform the position
        temp = projection_viewMatrix * (m_transform * temp);
        temp.homogenize();
        
        Structures::Vertex result(temp, vertex.m_color);
        
        temp = LibMath::Vector4(vertex.m_normal, 1.0f);     // transform the normal
        temp = transposeTransformMatrix * temp;
        temp.homogenize();

        result.m_normal = LibMath::Vector3 (temp.getX(), temp.getY(), temp.getZ());
        result.m_u = vertex.m_u;
        result.m_v = vertex.m_v;
        result.m_color.m_a *= m_alpha;

        
        result.m_normal.normalize();
        transformed.m_vertices.push_back(result);
        
    }

    return transformed;
}

Structures::Mesh Structures::Entity::getProjectedMesh(Mesh transformedMesh, LibMath::Matrix4 projectionMatrix, LibMath::Matrix4 viewMatrix)
{
    Structures::Mesh projectedMesh;

    projectedMesh.m_indices = transformedMesh.m_indices;

    for each(Structures::Vertex vertex in transformedMesh.m_vertices)
    {
        LibMath::Vector4 temp(vertex.m_position, 1.0f);

        temp = projectionMatrix * viewMatrix * temp;
        //temp =  temp * viewMatrix * projectionMatrix;

        temp.homogenize();

        //std::cout << "x: " << temp.getX() << " y: " << temp.getY() << " z: " << temp.getZ() << " k: " << temp.getK() << '\n';
        projectedMesh.m_vertices.push_back(Structures::Vertex(temp, vertex.m_color));
    }

    return projectedMesh;
}

Structures::Mesh Structures::Entity::getCameraProjectedMesh(Mesh transformedMesh, LibMath::Matrix4 viewMatrix)
{
    Structures::Mesh viewMesh;

    viewMesh.m_indices = transformedMesh.m_indices;

    for each(Structures::Vertex vertex in transformedMesh.m_vertices)
    {
        LibMath::Vector4 temp(vertex.m_position, 1.0f);

        temp = viewMatrix * temp;

        temp.homogenize();

        //std::cout << "x: " << temp.getX() << " y: " << temp.getY() << " z: " << temp.getZ() << " k: " << temp.getK() << '\n';
        viewMesh.m_vertices.push_back(Structures::Vertex(temp, vertex.m_color));
    }

    return viewMesh;
}
