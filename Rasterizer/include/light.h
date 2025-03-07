#ifndef LIGHT_H
#define LIGHT_H

#include "LibMath/Vector.h"

namespace Structures
{
	struct Light
	{
							Light(float ambient, float diffuse, float specular, LibMath::Vector3 position);

		float				m_ambient = 0.f;
		float				m_diffuse = 0.f;
		float				m_specular = 0.f;

		LibMath::Vector3	m_position;
	};
}


#endif