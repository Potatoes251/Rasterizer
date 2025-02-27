#ifndef MESH_H
#define MESH_H

#include <vector>

#include "vertex.h"
#include "plan.h"
#include "texture.h"

namespace Structures
{
	struct Mesh
	{
		Mesh(std::vector<Vertex> vertices, std::vector<int> indices);
		Mesh();

		static Mesh* createCube(Texture* tex, Structures::Color color);
		static Mesh* createCube(Structures::Color color);
		static void setNormalsFace(Mesh* cubeMesh);
		static void setNormalsSphere(Mesh* cubeMesh);
		static void setNormals(Mesh* cubeMesh);

		static Mesh* createSphere(int widthSegments = 15, int heightSegments = 15, float radius = 0.6);

		std::vector<Vertex> m_vertices;
		std::vector<int> m_indices;

		Texture* m_texture = nullptr;
	};
}


#endif