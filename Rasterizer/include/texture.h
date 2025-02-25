#ifndef TEXTURE_H
#define TEXTURE_H

#include "color.h"

namespace Structures
{
	struct Texture
	{
		Texture() = delete;
		Texture(unsigned int width, unsigned int height, Color colors = COLOR_BLACK, float zMax = -5.f);
		//Texture(unsigned int width, unsigned int height, Color colors = COLOR_BLACK);
		Texture(char const* texture);
		void setPixelColor(unsigned int x, unsigned int y, const Color& c = COLOR_WHITE, float alpha = 1.f);

		void drawTexture();
		
		float buffer(int const x, int const y);

		void updateBuffer(int const x, int const y, float zMax);

		void clearTexture(const Color& = COLOR_BLACK);

		unsigned int m_width;
		unsigned int m_height;
		Color* m_pixels;

		float* m_zBuffer;

	};

}


#endif