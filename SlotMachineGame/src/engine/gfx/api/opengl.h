#pragma once
#include <glad/glad.h>
#include <engine/assert.h>
namespace oct
{
	class gl
	{
	public:
		gl(const gl&) = delete;
		class index_buffer;
		class vertex_buffer;
		class vertex_array;
		class shader;
		class context;
		class texture2d;
	};

	static GLenum shader_datatype_to_opengl_datatype(gfx::shader_datatype type)
	{
		switch (type)
		{
		case gfx::shader_datatype::float1:  return GL_FLOAT;
		case gfx::shader_datatype::float2:  return GL_FLOAT;
		case gfx::shader_datatype::float3:  return GL_FLOAT;
		case gfx::shader_datatype::float4:  return GL_FLOAT;
		case gfx::shader_datatype::mat3:    return GL_FLOAT;
		case gfx::shader_datatype::mat4:    return GL_FLOAT;
		case gfx::shader_datatype::int1:    return GL_INT;
		case gfx::shader_datatype::int2:    return GL_INT;
		case gfx::shader_datatype::int3:    return GL_INT;
		case gfx::shader_datatype::int4:    return GL_INT;
		case gfx::shader_datatype::boolean: return GL_BOOL;
		}
		return 0;
	}
}