#pragma once
#include <engine/gfx/gfx.h>
#include <vector>
namespace oct
{
	class gfx::texture2d
	{
	public:
		virtual ~texture2d() = default;
		virtual void bind() const = 0;
		virtual auto id() const-> uint32_t = 0;
		virtual void unbind() const = 0;
	};
}
#include <engine/gfx/api/gl/gl_texture.hpp>