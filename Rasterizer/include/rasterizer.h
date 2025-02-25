#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "scene.h"
#include "texture.h"

namespace Structures
{
	struct Rasterizer
	{
		void renderScene(Scene* pScene, Texture* pTexture, bool wireframe = false);

		float edgeFunction(Vertex v1, Vertex v2, Vertex v3);

		Color getNearestTexel(Vertex v, Texture* tex);
		Color getTexelColor(Vertex v, Texture* tex);	// get the color of the pixel to draw by using bilenear filtering

		void fillTriangle(Vertex v1, Vertex v2, Vertex v3, Texture& sceneTexture, Texture* objectTexture, float alpha, std::vector<Structures::Light> lights);

		void drawLine(Vertex v1, Vertex v2, Texture& tex);

		Structures::Vertex projectVertex(Vertex v, float width, float height);
	};
}

#endif