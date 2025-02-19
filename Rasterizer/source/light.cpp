#include "light.h"

Structures::Light::Light(float ambient, float diffuse, float specular, LibMath::Vector3 position)
{
	m_ambient = ambient;
	m_diffuse = diffuse;
	m_specular = specular;
	m_position = position;
}
