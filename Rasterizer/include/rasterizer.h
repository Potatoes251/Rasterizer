#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "scene.h"
#include "texture.h"

namespace Structures
{
	struct Rasterizer
	{
		void renderScene(Scene* pScene, Texture* pTexture, bool wireframe = false, float near = 3, float far = -3);

		float edgeFunction(Vertex v1, Vertex v2, Vertex v3);

		void fillTriangle(Vertex v1, Vertex v2, Vertex v3, Texture& tex);

		void drawLine(int x0, int y0, int x1, int y1, Texture& tex);
	};
}

#endif