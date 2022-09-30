#pragma once
#include <engine/gfx/gfx.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
namespace oct
{
	// Полиморфизм, как вы просили.
	class gfx::object
	{
	public:
		texture2d* texture = nullptr;
		virtual ~object() = default;
		constexpr auto VBO() const->gfx::vertex_buffer& { return *s_vbo; }
		constexpr auto VAO() const->gfx::vertex_array& { return *s_vao; }
		virtual void on_draw() = 0;
	protected:
		static inline const gfx::context* s_ctx;
		static inline gfx::vertex_buffer* s_vbo;
		static inline gfx::vertex_array* s_vao;
		static inline gfx::shader* s_shader;
		static inline uint32_t s_index_count;
		friend class renderer2d;
	};
}