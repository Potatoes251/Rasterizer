#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "scene.h"
#include "texture.h"
#include "raylib.h"

namespace Structures
{
	struct Rasterizer
	{
		void renderScene(Scene* pScene, Texture* pTexture, LibMath::Matrix4 const& projectionMatrix, LibMath::Matrix4 const& viewMatrix, bool wireframe = false);

		float edgeFunction(Vertex v1, Vertex v2, Vertex v3);

		void fillTriangle(Vertex v1, Vertex v2, Vertex v3, Texture& tex);

		void drawLine(int x0, int y0, int x1, int y1, Texture& tex);
	};

	struct Camera
	{
		LibMath::Vector3 m_position;

		float m_pitch = 0.f;
		float m_yaw = 0.f;
	};

	LibMath::Matrix4 createViewMatrix(const LibMath::Vector3& eye, float pitch = 0.f, float yaw = 0.f);

	LibMath::Matrix4 lookAt(const LibMath::Vector3& eye, const LibMath::Vector3 target = LibMath::Vector3(0.f, 0.f, 1.f), LibMath::Vector3 up = LibMath::Vector3(0.f, 1.f, 0.f));

	void inputManager(Structures::Camera& camera);
}

#endif