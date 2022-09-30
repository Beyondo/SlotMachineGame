#pragma once
#include <engine/gfx/gfx.h>
#include <vector>
namespace oct
{
	class gfx::vertex_array
	{
	public:
		virtual ~vertex_array() = default;
		virtual void add_vertex_buffer(const gfx::vertex_buffer* buf) = 0;
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual void set_index_buffer(const gfx::index_buffer* indexBuf) = 0;
		virtual auto vertex_buffers() const -> std::vector<gfx::vertex_buffer*> = 0;
		virtual auto index_buffer() const -> const gfx::index_buffer& = 0;
	};
}
#include <engine/gfx/api/gl/gl_vertex_array.hpp>