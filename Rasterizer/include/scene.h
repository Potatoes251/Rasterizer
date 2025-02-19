#ifndef SCENE_H
#define SCENE_H

#include "entity.h"
#include "texture.h"

namespace Structures
{
	struct Scene
	{
		Scene() = default;
		Scene(std::vector<Entity> entities);

		static Scene createProjectScene(Structures::Texture& tex);

		std::vector<Entity> m_entities;
	};

}
#endif