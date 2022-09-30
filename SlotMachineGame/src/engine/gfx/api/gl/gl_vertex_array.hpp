#pragma once
#include <engine/gfx/api/opengl.h>
#include <engine/gfx/buffer.h>
#include <engine/gfx/vertex_array.h>
//
#include <glad/glad.h>
#include <cstdint>
namespace oct
{
	class gl::vertex_array : public gfx::vertex_array
	{
	public:
		inline vertex_array()
		{
			glCreateVertexArrays(1, &m_id);
		}
		inline virtual void add_vertex_buffer(const gfx::vertex_buffer* buf) override
		{
			OCTAVIAN_ASSERT_PTR(buf);
			this->bind();
			buf->bind();
			const auto& layout = buf->layout();
			for (const auto& element : layout)
			{
				switch (element.type)
				{
				case gfx::shader_datatype::float1:
				case gfx::shader_datatype::float2:
				case gfx::shader_datatype::float3:
				case gfx::shader_datatype::float4:
				{
					glEnableVertexAttribArray(m_vertex_buffer_index);
					glVertexAttribPointer(m_vertex_buffer_index,
						element.component_count(),
						shader_datatype_to_opengl_datatype(element.type),
						element.normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)element.offset);
					m_vertex_buffer_index++;
					break;
				}
				case gfx::shader_datatype::int1:
				case gfx::shader_datatype::int2:
				case gfx::shader_datatype::int3:
				case gfx::shader_datatype::int4:
				case gfx::shader_datatype::boolean:
				{
					glEnableVertexAttribArray(m_vertex_buffer_index);
					glVertexAttribIPointer(m_vertex_buffer_index,
						element.component_count(),
						shader_datatype_to_opengl_datatype(element.type),
						layout.GetStride(),
						(const void*)element.offset);
					m_vertex_buffer_index++;
					break;
				}
				case gfx::shader_datatype::mat3:
				case gfx::shader_datatype::mat4:
				{
					uint8_t count = element.component_count();
					for (uint8_t i = 0; i < count; i++)
					{
						glEnableVertexAttribArray(m_vertex_buffer_index);
						glVertexAttribPointer(m_vertex_buffer_index,
							count,
							shader_datatype_to_opengl_datatype(element.type),
							element.normalized ? GL_TRUE : GL_FALSE,
							layout.GetStride(),
							(const void*)(element.offset + sizeof(float) * count * i));
						glVertexAttribDivisor(m_vertex_buffer_index, 1);
						m_vertex_buffer_index++;
					}
					break;
				}
				default:
					throw std::exception("Unknown gfx::shader_datatype");
				}
			}
		}
		inline virtual void bind() const override
		{
			glBindVertexArray(m_id);
		}
		inline virtual void unbind() const override
		{
			glBindVertexArray(0);
		}
		inline virtual void set_index_buffer(const gfx::index_buffer* indexBuf) override
		{
			OCTAVIAN_ASSERT_PTR(indexBuf);
			glBindVertexArray(m_id);
			indexBuf->bind();
			m_indexBuf = indexBuf;
		}
		inline virtual auto vertex_buffers() const -> std::vector<gfx::vertex_buffer*> override
		{
			return m_vertexBuffers;
		}
		inline virtual auto index_buffer() const -> const gfx::index_buffer& override
		{
			return *m_indexBuf;
		}
		inline ~vertex_array()
		{
			glDeleteVertexArrays(1, &m_id);
		}
	private:
		uint32_t m_id;
		uint32_t m_vertex_buffer_index = 0;
		std::vector<gfx::vertex_buffer*> m_vertexBuffers;
		const gfx::index_buffer* m_indexBuf;
		friend class gl;
	};
}