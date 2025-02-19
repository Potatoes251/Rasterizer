#ifndef TEXTURE_H
#define TEXTURE_H

#include "color.h"

namespace Structures
{
	struct Texture
	{
		Texture() = delete;
		Texture(unsigned int width, unsigned int height, Color colors = COLOR_BLACK, float zMax = -5.f);

		void setPixelColor(unsigned int x, unsigned int y, const Color& c = COLOR_WHITE);

		void drawTexture() const;

		float buffer(int const x, int const y);

		void updateBuffer(int const x, int const y, float zMax);

		unsigned int m_width;
		unsigned int m_height;
		Color* m_pixels;

		float* m_zBuffer;

	};
}


#endif