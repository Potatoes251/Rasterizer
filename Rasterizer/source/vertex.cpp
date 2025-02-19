#include "vertex.h"

Structures::Vertex::Vertex(float x, float y, float z, Color color)
{
    m_position = LibMath::Vector3(x, y, z);
    m_color = color;
}

Structures::Vertex::Vertex(LibMath::Vector4 vec, Structures::Color color)
{
    m_position = LibMath::Vector3(vec.getX(), vec.getY(), vec.getZ());
    m_color = color;
}

Structures::Vertex::Vertex(LibMath::Vector3 vec, Structures::Color color)
{
    m_position = vec;
    m_color = color;
}

float Structures::Vertex::operator[](int index)
{
    return m_position[index];
}

void Structures::Vertex::setColor(Color color)
{
    m_color = color;
}