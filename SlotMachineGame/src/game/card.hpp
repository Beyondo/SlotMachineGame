#pragma once
#include <string>
#include <engine/renderer2d.h>
namespace oct
{
	class card : public quad
	{
	public:
		card(const std::string& name, const std::string& path, uint32_t id) : m_name(name), m_id(id)
		{
			int x, y, channels;
			stbi_uc* texture_data = stbi_load(path.c_str(), &x, &y, &channels, 4);
			texture = renderer2d::context()->create_texture2d(texture_data, x, y, channels);
			stbi_image_free(texture_data);
		}
		bool operator<(const card& rhs) const noexcept
		{
			return this->m_id < rhs.m_id; // for example
		}
		constexpr auto id() const -> uint32_t { return this->m_id; }
		constexpr auto name() const -> const std::string& { return this->m_name; }
	private:
		virtual void on_draw() override
		{

		}
		std::string m_name;
		uint32_t m_id;
	};
}