#pragma once
#include <engine/gfx/gfx.h>
#include <vector>
#include <string>
namespace oct
{
	struct gfx::buffer_element
	{
		std::string name;
		gfx::shader_datatype type;
		uint32_t size;
		size_t offset;
		bool normalized;

		buffer_element() = default;

		buffer_element(gfx::shader_datatype type, const std::string& name, bool normalized = false)
			: name(name), type(type), size(gfx::get_datatype_size(type)), offset(0), normalized(normalized)
		{
		}
		uint32_t component_count() const
		{
			return gfx::get_component_count(type);
		}
	};
	class gfx::buffer_layout
	{
	public:
		buffer_layout() {}

		buffer_layout(std::initializer_list<gfx::buffer_element> elements)
			: m_elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		uint32_t GetStride() const { return m_stride; }
		const std::vector<gfx::buffer_element>& GetElements() const { return m_elements; }

		std::vector<gfx::buffer_element>::iterator begin() { return m_elements.begin(); }
		std::vector<gfx::buffer_element>::iterator end() { return m_elements.end(); }
		std::vector<gfx::buffer_element>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<gfx::buffer_element>::const_iterator end() const { return m_elements.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			size_t offset = 0;
			m_stride = 0;
			for (auto& element : m_elements)
			{
				element.offset = offset;
				offset += element.size;
				m_stride += element.size;
			}
		}
	private:
		std::vector<gfx::buffer_element> m_elements;
		uint32_t m_stride = 0;
	};
	class gfx::vertex_buffer
	{
	public:
		virtual ~vertex_buffer() = default;
		virtual auto layout() const -> const gfx::buffer_layout& = 0;
		virtual void set_layout(const gfx::buffer_layout& layout) = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	};
	class gfx::index_buffer
	{
	public:
		virtual ~index_buffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint32_t count() const = 0;
	};
}
#include <engine/gfx/api/gl/gl_buffer.hpp>