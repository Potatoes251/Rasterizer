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

		void fillTriangle(Vertex v1, Vertex v2, Vertex v3, Texture& sceneTexture, Texture* objectTexture);

		void drawLine(Vertex v1, Vertex v2, Texture& tex);

		Structures::Vertex projectVertex(Vertex v, float width, float height);
	};
}

#endif