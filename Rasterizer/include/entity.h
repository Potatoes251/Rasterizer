#ifndef ENTITY_H
#define ENTITY_H

#include "LibMath/Matrix.h"

#include "mesh.h"
#include "texture.h"

namespace Structures
{
	struct Entity
	{
		Entity() = default;
		Entity(Mesh* mesh, LibMath::Matrix4 transform, Texture* tex = nullptr);
		Entity(Entity const&);

		Entity& operator=(Entity const& other);

		Mesh getTransformedMesh(void);

		LibMath::Matrix4 m_transform;
		Mesh* m_mesh = nullptr;
		Texture* m_texture = nullptr;
	};
}


#endif