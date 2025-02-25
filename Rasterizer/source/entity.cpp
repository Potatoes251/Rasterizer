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

Structures::Mesh Structures::Entity::getTransformedMesh(LibMath::Matrix4 projection_viewMatrix)
{
    Mesh transformed;
    LibMath::Vector4 temp;

    transformed.m_indices = m_mesh->m_indices;

    for each(Structures::Vertex vertex in m_mesh->m_vertices)
    { // optimize later
        temp = LibMath::Vector4(vertex.m_position, 1.f);

        temp = projection_viewMatrix * (m_transform * temp);

        temp.homogenize();

        //std::cout << "x: " << temp.getX() << " y: " << temp.getY() << " z: " << temp.getZ() << " k: " << temp.getK() << '\n';
        transformed.m_vertices.push_back(Structures::Vertex(temp, vertex.m_color));
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
