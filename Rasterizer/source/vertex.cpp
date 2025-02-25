#include "vertex.h"
#include "light.h"

Structures::Vertex::Vertex(float x, float y, float z, Color color)
{
    m_position = LibMath::Vector3(x, y, z);
    m_normal = LibMath::Vector3::zero();
    m_color = color;
}

Structures::Vertex::Vertex(float x, float y, float z, float u, float v, Structures::Color color)
{
    m_position = LibMath::Vector3(x, y, z);
    m_normal = LibMath::Vector3::zero();
    m_color = color;
    m_u = u;
    m_v = v;
}

Structures::Vertex::Vertex(LibMath::Vector4 vec, Structures::Color color)
{
    m_position = LibMath::Vector3(vec.getX(), vec.getY(), vec.getZ());
    m_normal = LibMath::Vector3::zero();
    m_color = color;
}

Structures::Vertex::Vertex(const LibMath::Vector3 vec, const Structures::Color color)
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
    LibMath::Vector3 lightDirection = light.m_position - m_position;
    lightDirection.normalize();
    return std::max(m_normal.dot(lightDirection) * light.m_diffuse, 0.f);
}

float Structures::Vertex::calculateSpecular(Structures::Light light, Structures::Vertex viewPoint)
{
    LibMath::Vector3 lightDirection = light.m_position - m_position;
    lightDirection.normalize();

    LibMath::Vector3 viewPointDirection = viewPoint.m_position - m_position;
    viewPointDirection.normalize();

    LibMath::Vector3 half = lightDirection + viewPointDirection;
    half.normalize();

    return pow(std::max(half.dot(m_normal), 0.f), 32) * light.m_specular;
}

void Structures::Vertex::calculateLighting(Structures::Light light, Structures::Vertex viewPoint)
{
    unsigned char alpha = m_color.m_a;
    m_color = m_color * light.m_ambient + m_color * calculatediffuse(light) + m_color * calculateSpecular(light, viewPoint);
    m_color.m_a = alpha;
}

void Structures::Vertex::setColor(Color color)
{
    m_color = color;
}

std::ostream& Structures::operator<<(std::ostream& os, const Vertex& vertex)
{
    return os << "position -> x: " << vertex.m_position.getX() << "\ty: " << vertex.m_position.getY() << "\tz: " << vertex.m_position.getZ() << '\n';
}
