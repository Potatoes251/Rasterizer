#ifndef COLOR_H
#define COLOR_H

#define COLOR_RED Structures::Color(255, 0, 0, 255)
#define COLOR_GREEN Structures::Color(0, 255, 0, 255)
#define COLOR_BLUE Structures::Color(0, 0, 255, 255)
#define COLOR_WHITE Structures::Color(255, 255, 255, 255)
#define COLOR_BLACK Structures::Color(0, 0, 0, 255)

namespace Structures
{
	struct Color
	{
		Color() = default;

		Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		Color(Color const& other);

		Color& operator=(Color const& other);

		Color operator+(Color other);
		Color operator*(float val);

		unsigned char m_r = 0;

		unsigned char m_g = 0;

		unsigned char m_b = 0;

		unsigned char m_a = 0;

	};
}


#endif