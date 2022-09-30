#include "window.h"
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
namespace oct
{
	window::window(int width, int height, const std::string& title) : m_width(width), m_height(height)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		m_handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_handle);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			throw std::exception("Couldn't load OpenGL");
		glViewport(0, 0, width, height);
	}
	auto window::handle() const-> GLFWwindow*
	{
		return this->m_handle;
	}
	void window::swap_buffers() const
	{
		glfwSwapBuffers(m_handle);
	}
	void window::poll_events() const
	{
		glfwPollEvents();
	}
	bool window::running() const
	{
		return static_cast<bool>(!glfwWindowShouldClose(m_handle));
	}
}