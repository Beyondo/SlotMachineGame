#pragma once
#include <engine/gfx/object.h>
namespace oct
{
	class circle : public gfx::object
	{
	public:
		glm::vec3 position;
		glm::vec2 radius;
		glm::vec4 color;
		static inline void init(const gfx::context* ctx)
		{
			//s_index_count = 256;
			//gfx::vertex circle_vertices[...] =
			//{
			//	// positions            // colors               // texture coords
			//	{{ 1.0f,  1.0f, 0.0f },
			// .... circles are for noobs.
		}
	};
}