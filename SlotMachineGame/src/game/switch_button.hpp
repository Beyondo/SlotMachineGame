#pragma once
#include <engine/event.hpp>
#include <engine/engine.h>
namespace oct
{
	class switch_button;
	class switch_button_click_event : public oct::event
	{
	public:
		switch_button_click_event(switch_button& btn) : m_button(btn) { }
		constexpr auto button() -> switch_button& { return m_button; }
	private:
		switch_button& m_button;
	};
	class switch_button : public oct::quad
	{
	public:
		switch_button()
		{
			// Я мог бы использовать freetype и целая система графического интерфейса, но игра содержит только 2 слова - Start и Stop... так просто "pre-load" их и все.
			int x, y, channels;
			stbi_uc* texture_data = stbi_load("assets/images/start.png", &x, &y, &channels, 4);
			m_startTex = renderer2d::context()->create_texture2d(texture_data, x, y, channels);
			stbi_image_free(texture_data);
			texture_data = stbi_load("assets/images/stop.png", &x, &y, &channels, 4);
			m_stopTex = renderer2d::context()->create_texture2d(texture_data, x, y, channels);
			stbi_image_free(texture_data);
			texture = m_startTex;
			ortho = true;
			//
		}
		void click()
		{
			switch_button_click_event e(*this);
			for (auto& handler : on_click.handlers())
				handler(e);
		}
		void switch_on()
		{
			this->texture = m_stopTex;
			set_speed(10.0f);
		}
		void switch_off()
		{
			this->texture = m_startTex;
			set_speed(0.0f);
		}
		void switch_state()
		{
			this->texture = this->texture == m_startTex ? m_stopTex : m_startTex;
		}
		void set_speed(float speed)
		{
			s_shader->bind();
			s_shader->set_float("u_speed", speed);
		}
		virtual void on_draw() override
		{

		}
		event_handler<switch_button_click_event> on_click;
	private:
		gfx::texture2d* m_startTex;
		gfx::texture2d* m_stopTex;
	};
}