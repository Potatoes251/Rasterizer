#include "LibMath/LibMath.h"
#include <vector>



namespace Structures
{
	struct Vertex
	{
		Vertex() = default;

		Vertex(float x, float y, float z);

		Vertex(LibMath::Vector4 vec);

		Vertex(LibMath::Vector3 vec);

		LibMath::Vector3 m_position;
	};

	struct Mesh
	{
		Mesh(std::vector<Vertex> vertices, std::vector<int> indices);

		Mesh();

		static Mesh* createCube();

		std::vector<Vertex> m_vertices;

		std::vector<int> m_indices;

	};

	struct Color
	{
		Color() = default;

		Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

		unsigned char m_r;

		unsigned char m_g;

		unsigned char m_b;

		unsigned char m_a;

	};

	struct Texture
	{
		Texture() = delete;

		Texture(unsigned int width, unsigned int height, Color colors = Color(0, 0, 0, 0));

		void setPixelColor(unsigned int x, unsigned int y, const Color& c = Color(255, 255, 255, 255));

		unsigned int m_width;

		unsigned int m_height;

		Color* m_pixels;

	};

	struct Entity
	{

		Entity(Mesh* mesh, LibMath::Matrix4 transform);

		Entity() = default;

		Entity(Entity const&);

		Mesh getTransformedMesh(void);

		Mesh* m_mesh = nullptr;

		LibMath::Matrix4 m_transform;
	};

	struct Scene
	{
		Scene(std::vector<Entity> entities);

		std::vector<Entity> m_entities;
	};

	struct Rasterizer
	{
		void renderScene(Scene* pScene, Texture* pTexture);
	};

	void drawLine(int x0, int y0, int x1, int y1, Texture& tex);

}

