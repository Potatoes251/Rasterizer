#ifndef LIGHT_H
#define LIGHT_H

#include "LibMath/Vector.h"

namespace Structures
{
	struct Light
	{
		Light(float ambient, float diffuse, float specular, LibMath::Vector3 position);

		float m_ambient;
		float m_diffuse;
		float m_specular;

		LibMath::Vector3 m_position;
	};
}


#endif