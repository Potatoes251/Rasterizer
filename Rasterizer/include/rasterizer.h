#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "scene.h"
#include "texture.h"
#include "raylib.h"

namespace Structures
{
	struct Rasterizer
	{
		void		renderScene(Scene* pScene, Texture* pTexture, LibMath::Matrix4 const& projectionMatrix, LibMath::Matrix4 const& viewMatrix, bool wireframe = false);

		float		edgeFunction(Vertex v1, Vertex v2, Vertex v3);

		//Color		getNearestTexel(Vertex v, Texture* tex);
		Color		getTexelColor(Vertex v, Texture* tex);	// get the color of the pixel to draw by using bilenear filtering

		void		fillTriangle(Vertex v1, Vertex v2, Vertex v3, Texture& sceneTexture, Texture* objectTexture, float alpha, std::vector<Structures::Light> lights);

		void		drawLine(Vertex v1, Vertex v2, Texture& tex);

		Structures::Vertex		projectVertex(Vertex v, float width, float height);
	};

	struct Camera
	{
		LibMath::Vector3	m_position;
		float				m_pitch = 0.f;
		float				m_yaw = 0.f;
	};

	LibMath::Matrix4		createViewMatrix(const LibMath::Vector3& eye, float pitch = 0.f, float yaw = 0.f);

	LibMath::Matrix4		lookAt(const LibMath::Vector3& eye, const LibMath::Vector3 target = LibMath::Vector3(0.f, 0.f, 1.f), LibMath::Vector3 up = LibMath::Vector3(0.f, 1.f, 0.f));

	void					inputManager(Structures::Camera& camera, bool& wireframe);
	void					mainLoop(Structures::Camera& camera, Texture& texture, Scene& scene, LibMath::Matrix4& projectionMatrix);
	void					deleteAndCloseWindow(Scene& scene);
}

#endif