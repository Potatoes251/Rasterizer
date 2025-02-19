#ifndef VERTEX_H
#define VERTEX_H

#include "LibMath/vector.h"
#include "color.h"

namespace Structures
{
	struct Vertex
	{
		Vertex() = default;
		Vertex(float x, float y, float z, Structures::Color color = COLOR_WHITE);
		Vertex(LibMath::Vector4 vec, Structures::Color color = COLOR_WHITE);
		Vertex(LibMath::Vector3 vec, Structures::Color color = COLOR_WHITE);

		float operator[](int index); // return the x, y or z coordinate of the position

		void setColor(Color color);

		LibMath::Vector3 m_position;
		Structures::Color m_color;
	};
}


#endif