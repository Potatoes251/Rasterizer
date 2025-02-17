#include "LibMath/LibMath.h"
#include <vector>



namespace Structures
{
	struct Vertex
	{
		Vertex() = default;

		Vertex(float x, float y, float z);

		LibMath::Vector3 m_position;
	};

	struct Mesh
	{
		Mesh(std::vector<Vertex> vertices, std::vector<int> indices);

		Mesh() = default;

		static Mesh* createCube();

		std::vector<Vertex> m_vertices;

		std::vector<int> m_indices;

	};

	struct Color
	{
		Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

		unsigned char m_r;

		unsigned char m_g;

		unsigned char m_b;

		unsigned char m_a;

	};

	struct Texture
	{
		Texture() = delete;

		void setPixelColor(unsigned int x, unsigned int y, const Color& c);

		unsigned int m_width;

		unsigned int m_height;

		Color* m_pxiels;

	};

	struct Entity
	{
		Mesh* m_mesh;

		LibMath::Matrix4 m_transform;
	};

	struct Scene
	{
		std::vector<Entity> m_entities;
	};

	struct Rasterizer
	{
		void renderScene(Scene* pScene, Texture* pTexture);
	};

}