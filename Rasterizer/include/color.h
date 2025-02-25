#ifndef COLOR_H
#define COLOR_H

#define COLOR_RED		Structures::Color(255, 0, 0, 255)
#define COLOR_GREEN		Structures::Color(0, 255, 0, 255)
#define COLOR_BLUE		Structures::Color(0, 0, 255, 255)
#define COLOR_WHITE		Structures::Color(255, 255, 255, 255)
#define COLOR_BLACK		Structures::Color(0, 0, 0, 255)

#define COLOR_YELLOW	Structures::Color(255, 255, 0, 255)
#define COLOR_CYAN		Structures::Color(0, 255, 255, 255)
#define COLOR_MAGENTA	Structures::Color(255, 0, 255, 255)
#define COLOR_ORANGE	Structures::Color(255, 165, 0, 255)
#define COLOR_PURPLE	Structures::Color(128, 0, 128, 255)
#define COLOR_BROWN		Structures::Color(165, 42, 42, 255)
#define COLOR_GRAY		Structures::Color(128, 128, 128, 255)
#define COLOR_PINK		Structures::Color(255, 192, 203, 255)
#define COLOR_LIME		Structures::Color(50, 205, 50, 255)
#define COLOR_GOLD		Structures::Color(255, 215, 0, 255)

namespace Structures
{
	struct Color
	{
		Color() = default;

		Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		Color(Color const& other);

		Color& operator=(Color const& other);

		//Color operator+(Color other);

		//Color operator*(float val) const ;

		unsigned char m_r = 0;

		unsigned char m_g = 0;

		unsigned char m_b = 0;

		unsigned char m_a = 255;

	};
	Color operator*(Color color, float val);

	Color operator-(Color c1, Color c2);

	Color operator+(Color c1, Color c2);
}


#endif