#pragma once
#include <string>
struct GLFWwindow;
namespace oct
{
	class window
	{
	public:
		inline window() : m_handle(nullptr), m_width(0), m_height(0) {}
		/** Инициализирует window
		* \width Ширина window
		* \height Высота window
		* \title Заголовок window
		*/
		window(int width, int height, const std::string& title);
		void swap_buffers() const;
		auto handle() const->GLFWwindow*;
		void poll_events() const;
		/** Активное состояние window
		* \return Работает ли window по-прежнему
		*/
		bool running() const;
		constexpr auto width() const { return static_cast<float>(m_width); }
		constexpr auto height() const { return static_cast<float>(m_height); }
	private:
		GLFWwindow* m_handle;
		int m_width, m_height;
	};
}

