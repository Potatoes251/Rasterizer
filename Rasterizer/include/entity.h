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

		Mesh getTransformedMesh(LibMath::Matrix4 projection_viewMatrix);

		static Mesh getProjectedMesh(Mesh transformedMesh, LibMath::Matrix4 projectionMatrix, LibMath::Matrix4 viewMatrix); // projected verteces are not normalized 

		static Mesh getCameraProjectedMesh (Mesh transformedMesh, LibMath::Matrix4 viewMatrix);


		Mesh* m_mesh = nullptr;
		LibMath::Matrix4 m_transform;
	};
}


#endif