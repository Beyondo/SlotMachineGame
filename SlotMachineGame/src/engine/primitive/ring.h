#pragma once
#include <engine/gfx/object.h>
namespace oct
{
	class quad;
	// На самом деле нам не нужно его рисовать.
	class ring : public gfx::object
	{
	public:
		glm::vec3 position = glm::vec3(0.0f, 0.0f, -3.0f);
		glm::vec3 size = glm::vec3(1.0f);
		glm::vec4 color = glm::vec4(1.0f);
		static inline void init(const gfx::context* ctx)
		{
			//s_index_count = 6;
			//gfx::vertex circle_vertices[4] =
			//{
			//	// positions            // colors               // texture coords
			//	{{ 1.0f,  1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }}, // top right
			//	{{ 1.0f, -1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f }}, // bottom right
			//	{{-1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }}, // bottom left
			//	{{-1.0f,  1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f }}  // top left 
			//};
			//gfx::buffer_layout layout({
			//{ gfx::shader_datatype::float3, "a_Position" },
			//{ gfx::shader_datatype::float3, "a_Color" },
			//{ gfx::shader_datatype::float2, "a_TexCoord" },
			//	});
			//s_shader = ctx->compile_shader<path>("assets/shaders/circle.vert", "assets/shaders/circle.frag");
			//s_vao = ctx->create_vertex_array();
			//s_vbo = ctx->create_buffer(circle_vertices, sizeof(circle_vertices));
			//s_vbo->set_layout(layout);
			//s_vao->add_vertex_buffer(s_vbo);
			//uint32_t indices[] = {
			//	0, 1, 3,
			//	1, 2, 3
			//};
			//gfx::index_buffer* quadIB = ctx->create_index_buffer(indices, s_index_count);
			//s_vao->set_index_buffer(quadIB);
		}
	};
}