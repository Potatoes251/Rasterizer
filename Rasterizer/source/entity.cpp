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

Structures::Mesh Structures::Entity::getTransformedMesh(LibMath::Matrix4 projectionMatrix)
{
    Mesh transformed;
    LibMath::Vector4 temp;
    LibMath::Matrix4 rowMajor = projectionMatrix;

    transformed.m_indices = m_mesh->m_indices;

    for each(Structures::Vertex vertex in m_mesh->m_vertices)
    {
        temp = LibMath::Vector4(vertex.m_position, 1.0f);

        temp =  rowMajor * (m_transform * temp);

        temp.homogenize();

        transformed.m_vertices.push_back(Structures::Vertex(temp, vertex.m_color));
    }

    return transformed;
}

LibMath::Vector4 Structures::Entity::projectMesh(LibMath::Vector4 transformedMeshPosition, LibMath::Matrix4 projectionMatrix)
{
    LibMath::Vector4 tempMeshPosition = LibMath::Vector4(transformedMeshPosition);

    LibMath::Matrix4 rowMajor = projectionMatrix.transpose();

    tempMeshPosition = rowMajor * tempMeshPosition;

    tempMeshPosition.homogenize();

    return tempMeshPosition;
}
