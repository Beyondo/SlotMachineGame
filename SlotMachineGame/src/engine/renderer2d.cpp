#include "renderer2d.h"
#include <glad/glad.h>
#include <engine/gfx/context.h>
#include <engine/gfx/api/gl/gl_context.hpp>
#include <GLFW/glfw3.h>
using namespace glm;
namespace oct
{
	auto renderer2d::init(api API, const window* win) -> gfx::context*
	{
		mainWindow = win;
		gfx::context* ctx = render_cmd::setup_graphics(api::opengl, win);
		quad::init(ctx);
		return ctx;
	}
	void renderer2d::draw_quad(const vec2& position, const vec2& size, const vec4& color, const gfx::texture2d* texture)
	{
		renderer2d::draw_quad(vec3(position.x, position.y, -1.0f), size, color, texture);
	}
	void renderer2d::draw_quad(const vec3& position, const vec2& size, const vec4& color, const gfx::texture2d* texture)
	{
		mat4 model = translate(mat4(1), position) * scale(mat4(1), vec3(size, 1.0f));
		mat4 transform = camera::calculate_transform(mainWindow->width() / mainWindow->height(), model);
		renderer2d::draw_quad(transform, color, texture);
	}
	void renderer2d::draw_quad_rotated(const vec3& position, const vec2& size, const vec3 rotationAxes, float rotationAngle,
		const vec4& color, const gfx::texture2d* texture, bool ortho)
	{
		mat4 model = translate(mat4(1), position) * rotate(mat4(1), rotationAngle, rotationAxes) * scale(mat4(1), vec3(size, 1.0f));
		mat4 transform = ortho ? glm::ortho(0.0f, mainWindow->width(), 0.0f, mainWindow->height(), 0.f, 1000.0f) * model:
			camera::calculate_transform(mainWindow->width() / mainWindow->height(), model);
		renderer2d::draw_quad(transform, color, texture);
	}
	void renderer2d::draw_quad(const mat4& transform, const vec4& color, const gfx::texture2d* texture)
	{
		quad::s_shader->bind();
		quad::s_shader->set_float("u_time", static_cast<float>(glfwGetTime()));
		quad::s_shader->set_mat4("u_transform", transform);
		if (texture)
		{
			quad::s_shader->set_bool("u_colorMode", false);
			quad::s_shader->set_int("u_texID", 0);
			texture->bind();
			renderer2d::flush();
			texture->unbind();
		}
		else
		{
			quad::s_shader->set_bool("u_colorMode", true);
			quad::s_shader->set_vec4("u_color", color);
			renderer2d::flush();
		}
	}
	void renderer2d::draw(quad* Quad)
	{
		if (!Quad->hidden)
		{
			renderer2d::draw_quad_rotated(Quad->position, Quad->size, Quad->rotation, Quad->rotation_angle, Quad->color, Quad->texture, Quad->ortho);
			Quad->on_draw();
		}
	}
	void renderer2d::draw(ring* Ring)
	{
		renderer2d::draw_quad(Ring->position, Ring->size, Ring->color, Ring->texture);
		Ring->on_draw();
	}
	void renderer2d::begin_projection(mat4 camera)
	{
	}
	void renderer2d::end_projection()
	{
	}
	void renderer2d::flush()
	{
		if (quad::s_index_count)
		{
			render_cmd::draw_indexed(quad::s_vao, quad::s_index_count);
		}
	}
	auto renderer2d::context()->gfx::context*
	{
		return render_cmd::context();
	}
}