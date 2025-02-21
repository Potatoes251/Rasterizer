#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"

#include "raylib.h"

#include <iostream>

#include "texture.h"

Structures::Texture::Texture(unsigned int width, unsigned int height, Color color)
{
    m_width = width;

    m_height = height;

    m_pixels = new Color[width * height];

    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            m_pixels[(j * width) + i] = color;
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
    std::cout << width << "X" << height << std::endl;

    m_width = width;
    m_height = height;
    m_pixels = new Color[width * height];
    
    std::memcpy(m_pixels, data, width * height * sizeof(Color));
}

void Structures::Texture::clearTexture(const Color& c)
{
    for (size_t i = 0; i < m_width; i++)
    {
        for (size_t j = 0; j < m_height; j++)
        {
            m_pixels[(j * m_width) + i] = c;
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
