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

		static Mesh* createSphere(int widthSegments = 15, int heightSegments = 15, float radius = 0.6);

		std::vector<Vertex> m_vertices;
		std::vector<int> m_indices;

	};
}


#endif