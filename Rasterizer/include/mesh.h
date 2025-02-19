#ifndef MESH_H
#define MESH_H

#include <vector>

#include "vertex.h"

namespace Structures
{
	struct Mesh
	{
		Mesh(std::vector<Vertex> vertices, std::vector<int> indices);
		Mesh();

		static Mesh* createCube();

		std::vector<Vertex> m_vertices;
		std::vector<int> m_indices;

	};
}


#endif