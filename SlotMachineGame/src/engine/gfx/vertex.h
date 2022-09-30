#pragma once
#include <engine/gfx/gfx.h>
#include <glm/glm.hpp>
namespace oct
{
	struct gfx::vertex
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 texture_coords;
	};
}