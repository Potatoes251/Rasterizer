#include "color.h"

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

//Structures::Color Structures::Color::operator+(Color other)
//{
//    return Color(m_r + other.m_r, m_g + other.m_g, m_b + other.m_b, m_a + other.m_a);
//}

//Structures::Color Structures::Color::operator*(float val) const
//{
//    return Color(m_r * val, m_g * val, m_b * val, m_a * val);
//}

Structures::Color Structures::operator*(Color color, float val)
{
    return Color(color.m_r * val, color.m_g * val, color.m_b * val, color.m_a * val);
}

Structures::Color Structures::operator-(Color c1, Color c2)
{
    return Color(c1.m_r - c2.m_r, c1.m_g - c2.m_g, c1.m_b - c2.m_b, c1.m_a - c2.m_a);
}

Structures::Color Structures::operator+(Color c1, Color c2)
{
    return Color(c1.m_r + c2.m_r, c1.m_g + c2.m_g, c1.m_b + c2.m_b, c1.m_a + c2.m_a);
}
