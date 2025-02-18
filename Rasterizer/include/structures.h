#include "LibMath/LibMath.h"
#include <vector>

#include "color.h"

namespace Structures
{
	struct Vertex
	{
		Vertex() = default;

		Vertex(float x, float y, float z, Structures::Color color = COLOR_WHITE);

		Vertex(LibMath::Vector4 vec, Structures::Color color = COLOR_WHITE);

		Vertex(LibMath::Vector3 vec);

		float operator[](int index);

		void setColor(Color color);

		LibMath::Vector3 m_position;
		Structures::Color m_color;
	};

	struct Mesh
	{
		Mesh(std::vector<Vertex> vertices, std::vector<int> indices);

		Mesh();

		static Mesh* createCube();

		std::vector<Vertex> m_vertices;

		std::vector<int> m_indices;

	};

	struct Texture
	{
		Texture() = delete;

		Texture(unsigned int width, unsigned int height, Color colors = COLOR_BLACK);

		void setPixelColor(unsigned int x, unsigned int y, const Color& c = COLOR_WHITE);

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
		void renderScene(Scene* pScene, Texture* pTexture, bool wireframe = true);

		float edgeFunction(Vertex v1, Vertex v2, Vertex v3);

		void fillTriangle(Vertex v1, Vertex v2, Vertex v3 ,Texture& tex);
	};

	void drawLine(int x0, int y0, int x1, int y1, Texture& tex);

}

