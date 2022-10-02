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
		static inline void on_switch_click(switch_button_click_event& e);
		static inline void load();
		static inline auto run() -> int
		{
			stbi_set_flip_vertically_on_load(1);
			win = new window(default_width, default_height, default_title);
			ctx = renderer2d::init(api::opengl, win);
			glfwSetCursorPosCallback(win->handle(), mouse_callback);
			glfwSetMouseButtonCallback(win->handle(), mouse_button_callback);
			glfwSetKeyCallback(win->handle(), key_callback);	
			glfwSwapInterval(1);
			normalCursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
			handCursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
			game::machine = new slot_machine();
			game::machine->switchButton.on_click += on_switch_click;
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
			glfwDestroyCursor(handCursor);
			glfwDestroyCursor(normalCursor);
			delete machine;
			delete ctx;
			delete win;
			return 0;
		}
		static inline void integration(float dt);
		static inline void rendering();
		static inline float speed = 1.0f;
		static inline bool editor_mode = false;
		static inline window* win;
	private:
		static inline GLFWcursor* handCursor;
		static inline GLFWcursor* normalCursor;
		static constexpr int default_width = 1152;
		static constexpr int default_height = 768;
		static constexpr const char* default_title = "Slot Machine Game Task - Ocavian Gaming";
		static inline gfx::context* ctx;
		static inline float dt = 0.001f; // Это решает, насколько плавно останавливается барабаны, есть более эффективные способы, такие как интерполяция, но вы не дали мне на это времени.
		static inline double t_prev = 0;
		static inline double accumulator = 0;
		//
		static inline slot_machine* machine;
		//
		static void mouse_button_callback(GLFWwindow* w, int button, int action, int mods)
		{
			if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
			{
				double xpos, ypos;
				glfwGetCursorPos(w, &xpos, &ypos);
				if (is_inside_button(static_cast<float>(xpos), static_cast<float>(ypos)))
					machine->switchButton.click();
			}
		}
		static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
		{
			float sensitivity = static_cast<float>(1000 * game::dt);
			if (editor_mode) camera::move(static_cast<float>(xposIn) * sensitivity, static_cast<float>(yposIn) * sensitivity);
			if (is_inside_button(static_cast<float>(xposIn), static_cast<float>(yposIn)))
			{
				glfwSetCursor(win->handle(), handCursor);
			}
			else
			{
				glfwSetCursor(win->handle(), normalCursor);
			}
		}
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);
			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			{
				if (!game::machine->running())
				{
					game::machine->switchButton.switch_on();
					game::machine->start();
				}
				else if (game::machine->peak_velocity())
				{
					game::machine->switchButton.switch_off();
					game::machine->stop();
				}
				
			}
			if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
			{
				if (game::editor_mode)
				{
					game::machine->switchButton.hidden = false;
					game::editor_mode = false;
					camera::editor_mode = false;
					camera::reset();
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				}
				else
				{
					game::machine->switchButton.hidden = true;
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
		static bool is_inside_button(float xpos, float ypos)
		{
			ypos = win->height() - ypos; // Преобразование в систему координат видового экрана
			glm::vec3 click_direction = glm::vec3(xpos, ypos, 0);
			glm::vec3 dist_from_center = glm::abs(click_direction - machine->switchButton.position);
			glm::vec2& size = machine->switchButton.size;
			return dist_from_center.x <= size.x && dist_from_center.y <= size.y;
		}
	};
}