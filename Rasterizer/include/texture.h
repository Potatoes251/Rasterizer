#ifndef TEXTURE_H
#define TEXTURE_H

#include "color.h"


namespace Structures
{
	struct Texture
	{
		Texture() = delete;
		Texture(unsigned int width, unsigned int height, Color colors = COLOR_BLACK);
		Texture(char const* texture);

		void clearTexture(const Color& c = COLOR_BLACK);
		void setPixelColor(unsigned int x, unsigned int y, const Color& c = COLOR_WHITE);

		void drawTexture() const;

		unsigned int m_width;
		unsigned int m_height;
		Color* m_pixels;

	};
}


#endif