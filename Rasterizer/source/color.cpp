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

Structures::Color Structures::operator*(Color color, float val)
{
    return Color(std::min(static_cast<int>(color.m_r * val), 255), std::min(static_cast<int>(color.m_g * val), 255),
                std::min(static_cast<int>(color.m_b * val), 255), std::min(static_cast<int>(color.m_a * val), 255));
}

Structures::Color Structures::operator-(Color c1, Color c2)
{
    return Color(std::max(static_cast<int>(c1.m_r - c2.m_r), 0), std::max(static_cast<int>(c1.m_g - c2.m_g), 0),
                std::max(static_cast<int>(c1.m_b - c2.m_b), 0), std::max(static_cast<int>(c1.m_a - c2.m_a), 0));
}

Structures::Color Structures::operator+(Color c1, Color c2)
{
    return Color(std::min(static_cast<int>(c1.m_r + c2.m_r), 255), std::min(static_cast<int>(c1.m_g + c2.m_g), 255),
                std::min(static_cast<int>(c1.m_b + c2.m_b), 255), std::min(static_cast<int>(c1.m_a + c2.m_a), 255));
}
