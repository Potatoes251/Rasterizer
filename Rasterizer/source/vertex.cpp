#include "vertex.h"
#include "light.h"

Structures::Vertex::Vertex(float x, float y, float z, Color color)
{
    m_position = LibMath::Vector3(x, y, z);
    m_normal = LibMath::Vector3::zero();
    m_color = color;
}

Structures::Vertex::Vertex(LibMath::Vector4 vec, Structures::Color color)
{
    m_position = LibMath::Vector3(vec.getX(), vec.getY(), vec.getZ());
    m_normal = LibMath::Vector3::zero();
    m_color = color;
}

Structures::Vertex::Vertex(LibMath::Vector3 vec, Structures::Color color)
{
    m_position = vec;
    m_normal = LibMath::Vector3::zero();
    m_color = color;
}

float Structures::Vertex::operator[](int index)
{
    return m_position[index];
}

float Structures::Vertex::calculatediffuse(Structures::Light light)
{
    LibMath::Vector3 lightDirection = m_position - light.m_position;
    lightDirection.normalize();
    return std::max(m_normal.dot(lightDirection) * light.m_diffuse, 0.f);
}

float Structures::Vertex::calculateSpecular(Structures::Light light, Structures::Vertex viewPoint)
{
    LibMath::Vector3 lightReflection = m_position - light.m_position;
    lightReflection.normalize();
    lightReflection.reflectOnto(m_normal);

    LibMath::Vector3 viewPointDirection = m_position - viewPoint.m_position;
    viewPointDirection.normalize();
    return std::max(viewPointDirection.dot(lightReflection) * light.m_specular, 0.f);
}

void Structures::Vertex::calculateLighting(Structures::Light light, Structures::Vertex viewPoint)
{
    Color diffuse = m_color * calculatediffuse(light);
    Color specular = m_color * calculateSpecular(light, viewPoint);
    m_color = m_color * light.m_ambient + m_color * calculatediffuse(light) + m_color * calculateSpecular(light, viewPoint);
}

void Structures::Vertex::setColor(Color color)
{
    m_color = color;
}