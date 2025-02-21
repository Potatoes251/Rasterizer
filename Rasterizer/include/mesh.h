#ifndef MESH_H
#define MESH_H

#include <vector>

#include "vertex.h"
#include "texture.h"

namespace Structures
{
	struct Mesh
	{
		Mesh(std::vector<Vertex> vertices, std::vector<int> indices);
		Mesh();

		static Mesh* createCube(Texture* tex);
		static Mesh* createCube();
		static void setCubeNormals(Mesh* cubeMesh);

		std::vector<Vertex> m_vertices;
		std::vector<int> m_indices;

		Texture* pTexture = nullptr;
	};
}


#endif