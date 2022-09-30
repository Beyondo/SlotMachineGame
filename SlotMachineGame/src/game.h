#pragma once
#include <stb_image.h>
#include <game/slot_machine.hpp>
#include <engine/engine.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
namespace oct
{
	class game
	{
	public:
		static inline void load();
		static inline auto run() -> int
		{
			stbi_set_flip_vertically_on_load(1);
			win = new window(default_width, default_height, default_title);
			ctx = renderer2d::init(api::opengl, win);
			glfwSetCursorPosCallback(win->handle(), mouse_callback);
			glfwSetKeyCallback(win->handle(), key_callback);
			glfwSwapInterval(1);
			load();
			while (win->running())
			{
				double t = glfwGetTime();
				processInput();
				if (t_prev > 0)
				{
					double frameTime = t - t_prev;
					if (frameTime > 0.25)
						frameTime = 0.25;
					accumulator += frameTime;
					while (accumulator >= dt)
					{
						integration(static_cast<float>(game::dt * game::speed));
						accumulator -= dt;
					}
				}
				rendering();
				ctx->swap_buffers();
				win->poll_events();
				t_prev = t;
			}
			return 0;
		}
		static inline void integration(float dt);
		static inline void rendering();
		static inline float speed = 1.0f;
		static inline bool editor_mode = false;
	private:
		// Я действительно жалел, что у меня не было времени абстрагировать больше кода вместо того, чтобы помещать необработанные команды OpenGL в main.	
		static constexpr int default_width = 1152;
		static constexpr int default_height = 768;
		static constexpr const char* default_title = "Slot Machine Game Task - Ocavian Gaming";
		static inline window* win;
		static inline gfx::context* ctx;
		static inline float dt = 0.001f; // Это решает, насколько плавно останавливается барабаны, есть более эффективные способы, такие как интерполяция, но вы не дали мне на это времени.
		static inline double t_prev = 0;
		static inline double accumulator = 0;
		//
		static inline slot_machine* machine;
		//

		static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
		{
			float sensitivity = static_cast<float>(1000 * game::dt);
			if (editor_mode) camera::move(static_cast<float>(xposIn) * sensitivity, static_cast<float>(yposIn) * sensitivity);
		}
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);
			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			{
				if (!game::machine->running()) game::machine->start();
				else if(game::machine->peak_velocity()) game::machine->stop();
				// never stop the machine while it is still gaining velocity
			}
			if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
			{
				if (game::editor_mode)
				{
					game::editor_mode = false;
					camera::editor_mode = false;
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				}
				else
				{
					game::editor_mode = true;
					camera::editor_mode = true;
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				}
			}
		}
		static void processInput()
		{
			GLFWwindow* handle = win->handle();
			if (editor_mode)
			{
				float speed = static_cast<float>(2.5 * game::dt);
				if (glfwGetKey(handle, GLFW_KEY_W) == GLFW_PRESS)
					camera::go_forward(speed);
				if (glfwGetKey(handle, GLFW_KEY_S) == GLFW_PRESS)
					camera::go_backward(speed);
				if (glfwGetKey(handle, GLFW_KEY_A) == GLFW_PRESS)
					camera::go_left(speed);
				if (glfwGetKey(handle, GLFW_KEY_D) == GLFW_PRESS)
					camera::go_right(speed);
			}
		}
	};
}