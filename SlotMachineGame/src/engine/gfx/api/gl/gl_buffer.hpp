#pragma once
#include <engine/gfx/api/opengl.h>
#include <engine/gfx/buffer.h>
#include <glad/glad.h>
#include <cstdint>
namespace oct
{
	class gl::vertex_buffer : public gfx::vertex_buffer
	{
	public:
		vertex_buffer(const void* vertices, uint32_t size)
		{
			glCreateBuffers(1, &m_id);
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		}
		virtual auto layout() const -> const gfx::buffer_layout & override
		{
			return *this->m_layout;
		}
		virtual void set_layout(const gfx::buffer_layout& layout) override
		{
			this->m_layout = &layout;
		}
		virtual void bind() const override
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
		}
		virtual void unbind() const override
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		~vertex_buffer()
		{
			glDeleteBuffers(1, &m_id);
		}
	private:
		const gfx::buffer_layout* m_layout;
		uint32_t m_id;
		friend class gl;
	};
	class gl::index_buffer : public gfx::index_buffer
	{
	public:
		index_buffer(uint32_t* indices, uint32_t count) : m_count(count)
		{
			glCreateBuffers(1, &m_id);
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
		}
		virtual ~index_buffer()
		{
			glDeleteBuffers(1, &m_id);
		}
		virtual void bind() const override
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		}
		virtual void unbind() const override
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		virtual uint32_t count() const override
		{
			return m_count;
		}
	private:
		uint32_t m_id;
		uint32_t m_count;
	};
}