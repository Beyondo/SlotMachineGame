#pragma once
#include <engine/window.h>
#include <engine/graphics.h>
#include <engine/camera.h>
#include <engine/primitive/quad.h>
#include <engine/primitive/circle.h>
#include <engine/primitive/ring.h>
#include <vector>
// Сокращение от Octavian
namespace oct
{
	enum class api
	{ 
		opengl, vulkan, directx
	};
	// Только один графический API - OpenGL.
	// Это нормально высокоуровневые конструкции, такие как renderer2d и render_cmd, статическими,
	// потому что они являются основными объектами движка.
	class renderer2d
	{
	public:
		/** Это самая важная функция.
		Он инициализирует все примитивные типы и сохраняет их VBO, VAO, а также компилирует их шейдеры и т.д.,
		Чтобы мы могли легко и мгновенно привязать их к любому преобразованию, 
		которое нам нравится, например, положение, размер и цвет.
		*/
		static auto init(api API, const window* win) -> gfx::context*;
		/** Начинается проекцию 2d-сцены */
		static void begin_projection(glm::mat4 camera = glm::mat4(0));
		static void draw_quad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const gfx::texture2d* texture = nullptr);
		static void draw_quad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const gfx::texture2d* texture = nullptr);
		static void draw_quad_rotated(const glm::vec3& position, const glm::vec2& size, const glm::vec3 rotationAxes, float rotationAngle, const glm::vec4& color, const gfx::texture2d* texture = nullptr);
		static void draw_quad(const glm::mat4& transform, const glm::vec4& color, const gfx::texture2d* texture = nullptr);
		static void draw(quad* Quad);
		static void draw(ring* Ring);
		/** Завершает проекцию 2d-сцены */
		static void end_projection();
		/** Flushes all draw commands */
		static void flush();
		static auto context()->gfx::context*;
	private:
		static inline const oct::window* mainWindow;
	};
	class render_cmd
	{
	public:
		static void draw_indexed(const gfx::vertex_array* VAO, uint32_t indexCount = 0)
		{
			ctx->draw_indexed(VAO, indexCount);
		}
		template<typename R, typename G, typename B, typename A>
		static constexpr void set_clear_color(R r, G g, B b, A a)
		{
			ctx->set_clear_color(static_cast<float>(r), static_cast<float>(g), static_cast<float>(b), static_cast<float>(a));
		}
		static void set_clear_color(const glm::vec4& color)
		{
			ctx->set_clear_color(color);
		}
		static void clear()
		{
			ctx->clear();
		}
		static constexpr auto context() -> gfx::context*
		{
			return ctx;
		}
		/** Инициализирует графический API */
		static constexpr auto setup_graphics(api API, const window* win) -> gfx::context*
		{
			if (win)
			{
				switch (API)
				{
				case api::opengl:
					ctx = new gl::context(win);
					return ctx;
				case api::vulkan:
					return nullptr;
				case api::directx:
					return nullptr;
				default:
					throw std::exception("Such API is not support by Octavian.");
				}
			}
			else
				throw std::exception("Renderer cannot be bound to a nullptr window");
		}
	private:
		static inline gfx::context* ctx;
	};
}