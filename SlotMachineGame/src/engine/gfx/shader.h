#pragma once
#include <engine/gfx/gfx.h>
//
#include <string>
#include <glm/glm.hpp>
namespace oct
{
	class gfx::shader
	{
	public:

		virtual ~shader() = default;
		virtual void bind() const = 0;
		virtual void set_bool(const std::string& name, bool value) const = 0;
		virtual void set_int(const std::string& name, int value) const = 0;
		virtual void set_float(const std::string& name, float value) const = 0;
		virtual void set_vec2(const std::string& name, const glm::vec2& vec) const = 0;
		virtual void set_vec3(const std::string& name, const glm::vec3& vec) const = 0;
		virtual void set_vec4(const std::string& name, const glm::vec4& vec) const = 0;
		virtual void set_mat2(const std::string& name, const glm::mat2& mat) const = 0;
		virtual void set_mat3(const std::string& name, const glm::mat3& mat) const = 0;
		virtual void set_mat4(const std::string& name, const glm::mat4& mat) const = 0;
	};
}
#include "api/gl/gl_shader.hpp"