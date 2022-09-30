#pragma once
#include <cstdint>
#include <glm/glm.hpp>
#include <string>
#include <vector>
enum read_type
{
	path,
	source,
};
namespace oct
{
	class gfx::shader;
	class gfx::rectangle;
	class gfx::vertex_buffer;
	class gfx::vertex_array;
	class gfx::context
	{
	public:
		virtual ~context() = default;
		virtual void draw_indexed(const gfx::vertex_array* VAO, uint32_t indexCount) const = 0;
		virtual void set_clear_color(float r, float g, float b, float a) const = 0;
		virtual void set_clear_color(const glm::vec4& color) const = 0;
		virtual void clear() const = 0;
		virtual auto create_shader_from_files(const char* vertexShaderSourceFile, const char* fragmentShaderSourceFile) const->gfx::shader* = 0;
		virtual auto create_buffer(const void* vertices, uint32_t size) const->gfx::vertex_buffer* = 0;
		virtual auto create_vertex_array() const->gfx::vertex_array* = 0;
		virtual auto create_index_buffer(uint32_t* indices, uint32_t size) const -> gfx::index_buffer* = 0;
		virtual auto create_texture2d(void* texture_data, uint32_t x, uint32_t y, uint32_t channels) const->texture2d* = 0;
		virtual void bind_shader(const gfx::shader* shader) const = 0;
		virtual void draw_triangles(const vertex_array& VAO, std::uint32_t offset, std::uint32_t count) const = 0;
		virtual void set_viewport(float x, float y, float width, float height) const = 0;
		virtual void swap_buffers() const = 0;
		/* Компилирует и загружает шейдерный объект
		* \vertex Вершинный шейдер
		* \fragment Фрагментный шейдер
		*/
		template<read_type op = source>
		auto compile_shader(const std::string& vertex, const std::string& fragment) const ->gfx::shader*
		{
			// Template должен быть определен в header.
			if constexpr (op == read_type::source)
				return nullptr;
			else if constexpr (op == read_type::path)
				return this->create_shader_from_files(vertex.c_str(), fragment.c_str());
			else
				static_assert("Such operation is not supported");
		}
		/* TODO */
		template<read_type op>
		static constexpr auto load_shader(const std::vector<char>& vertex, const std::vector<char>& fragment)->gfx::shader* = 0;
	};
}
#include <engine/gfx/api/gl/gl_context.hpp>