#ifndef SCENE_H
#define SCENE_H

#include "entity.h"
#include "texture.h"
#include "light.h"

namespace Structures
{
	struct Scene
	{
								Scene() = default;
								Scene(std::vector<Entity> entities, std::vector<Light> lights);

		static Scene			createProjectScene(Structures::Texture& tex);

		std::vector<Entity>		m_entities;
		std::vector<Light>		m_lights;
	};

}
#endif