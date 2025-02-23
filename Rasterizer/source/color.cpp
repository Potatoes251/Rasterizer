#include "color.h"
#include "mesh.h"

Structures::Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    m_r = r;
    m_g = g;
    m_b = b;
    m_a = a;
}

Structures::Color::Color(Color const& other)
{
    m_r = other.m_r;
    m_g = other.m_g;
    m_b = other.m_b;
    m_a = other.m_a;
}

Structures::Color& Structures::Color::operator=(Structures::Color const& other)
{
    m_r = other.m_r;
    m_g = other.m_g;
    m_b = other.m_b;
    m_a = other.m_a;

    return *this;
}

Structures::Color Structures::Color::operator+(Color other)
{
    return Color(std::min(m_r + other.m_r, 255), std::min(m_g + other.m_g, 255), 
                std::min(m_b + other.m_b,255), std::min(m_a + other.m_a, 255));
}

Structures::Color Structures::Color::operator*(float val)
{
    return Color(std::min(static_cast<int>(m_r * val), 255), std::min(static_cast<int>(m_g * val), 255),
                std::min(static_cast<int>(m_b * val), 255), std::min(static_cast<int>(m_a * val), 255));
}