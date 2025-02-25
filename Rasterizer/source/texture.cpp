#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"

#include "raylib.h"

#include <iostream>

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

Structures::Texture::Texture(char const* texture)
{
    int width, height, comp;
    unsigned char* data = stbi_load(texture, &width, &height, &comp, 4);

    if (data == nullptr)
    {
        std::cout << "stbi_load error : fail to load image\npath was : ";
    }

    m_width = width;
    m_height = height;
    m_pixels = new Color[width * height];
    
    std::memcpy(m_pixels, data, width * height * sizeof(Color));
    stbi_image_free(data);
}

void Structures::Texture::setPixelColor(unsigned int x, unsigned int y, const Color& c, float alpha)
{
    Structures::Color finalColor;
    if (alpha != 1.f)
    {
        Structures::Color backgroundColor = m_pixels[(y * m_width) + x];
        finalColor.m_r = backgroundColor.m_r * (1 - alpha) + c.m_r * alpha;
        finalColor.m_g = backgroundColor.m_g * (1 - alpha) + c.m_g * alpha;
        finalColor.m_b = backgroundColor.m_b * (1 - alpha) + c.m_b * alpha;
        finalColor.m_a = alpha + backgroundColor.m_a * (1 - alpha);
    }
    else
    {
        finalColor = c;
    }
    m_pixels[(y * m_width) + x] = finalColor;
}

void Structures::Texture::drawTexture()
{
    BeginDrawing();

    for (size_t i = 0; i < m_width; i++)
    {
        for (size_t j = 0; j < m_height; j++)
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

void Structures::Texture::clearTexture(const Color& color)
{
    for (size_t i = 0; i < 800; i++)
    {
        for (size_t j = 0; j < 600; j++)
        {
            m_pixels[j * m_width + i] = color;
            m_zBuffer[j * m_width + i] = -5.f;
            
        }
    }
}
