#pragma once
#include <engine/gfx/api/opengl.h>
#include <engine/gfx/texture.h>
#include <glad/glad.h>
#include <cstdint>
namespace oct
{
	class gl::texture2d : public gfx::texture2d
	{
	public:
		texture2d(void* texture_data, uint32_t x, uint32_t y, uint32_t channels)
		{
			glGenTextures(1, &m_id);
			glBindTexture(GL_TEXTURE_2D, m_id);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
			glGenerateMipmap(GL_TEXTURE_2D);
			
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		virtual auto id() const -> uint32_t override
		{
			return this->m_id;
		}
		virtual void bind() const override
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_id);
		}
		virtual void unbind() const override
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		~texture2d()
		{
			glDeleteTextures(1, &m_id);
		}
	private:
		uint32_t m_id;
		friend class gl;
	};
}