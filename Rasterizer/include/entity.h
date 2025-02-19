#ifndef ENTITY_H
#define ENTITY_H

#include "LibMath/Matrix.h"
#include "mesh.h"

namespace Structures
{
	struct Entity
	{
		Entity() = default;
		Entity(Mesh* mesh, LibMath::Matrix4 transform);
		Entity(Entity const&);

		Entity& operator=(Entity const& other);

		Mesh getTransformedMesh(LibMath::Matrix4 projectionMatrix);

		static LibMath::Vector4 projectMesh(LibMath::Vector4 transformedMeshPosition, LibMath::Matrix4 projectionMatrix);


		Mesh* m_mesh = nullptr;
		LibMath::Matrix4 m_transform;
	};
}


#endif