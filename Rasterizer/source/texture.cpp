#include "raylib.h"

#include "texture.h"

Structures::Texture::Texture(unsigned int width, unsigned int height, Color color, float zMax)
{
    m_width = width;

    m_height = height;

    m_pixels = new Color[width * height];

    m_zBuffer = new float[width * height];

    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            m_pixels[(j * width) + i] = color;

            m_zBuffer[(j * width) + i] = zMax;
        }
    }
}

void Structures::Texture::setPixelColor(unsigned int x, unsigned int y, const Color& c)
{
    m_pixels[(y * m_width) + x] = c;
}

void Structures::Texture::drawTexture() const
{
    BeginDrawing();

    for (size_t i = 0; i < 800; i++)
    {
        for (size_t j = 0; j < 600; j++)
        {
            Structures::Color color = m_pixels[j * m_width + i];
            ::Color raylibColor = { color.m_r, color.m_g, color.m_b, color.m_a };
            DrawPixel(i, j, raylibColor);
        }
    }
    EndDrawing();
}

float Structures::Texture::buffer(int const x, int const y)
{
    return m_zBuffer[(y * m_width) + x];
}

void Structures::Texture::updateBuffer(int const x, int const y, float zMax)
{
    m_zBuffer[(y * m_width) + x] = zMax;
}
