#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace oct
{
	class camera
	{
	public:
		static void go_forward(float speed = 1)
		{
			camera::position += camera::front * speed;
		}
		static void go_backward(float speed = 1)
		{
			camera::position -= camera::front * speed;
		}
		static void go_left(float speed = 1)
		{
			camera::position -= glm::normalize(glm::cross(camera::front, camera::up)) * speed;

		}
		static void go_right(float speed = 1)
		{
			camera::position += glm::normalize(glm::cross(camera::front, camera::up)) * speed;
		}
		static void move(float x, float y)
		{
			static bool firstMouse = true;
			static float lastX = 1152.0f / 2.0f;
			static float lastY = 768.0f / 2.0f;
			float xpos = static_cast<float>(x);
			float ypos = static_cast<float>(y);
			if (firstMouse)
			{
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
			}

			float xoffset = xpos - lastX;
			float yoffset = lastY - ypos;
			lastX = xpos;
			lastY = ypos;

			float sensitivity = 0.1f;
			xoffset *= sensitivity;
			yoffset *= sensitivity;
			camera::yaw += xoffset;
			camera::pitch += yoffset;
			if (camera::pitch > 89.0f)
				camera::pitch = 89.0f;
			if (pitch < -89.0f)
				camera::pitch = -89.0f;

			glm::vec3 front;
			front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			front.y = sin(glm::radians(pitch));
			front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			camera::front = glm::normalize(front);
		}
		static inline glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
		static inline glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
		static inline glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		static inline float yaw = -90.0f;
		static inline float pitch = 0.0f;
		static inline float fov = 45.0f;
		static inline float render_distance = 2.8f;
		static inline bool editor_mode = false;
		static inline auto calculate_transform(float aspectRatio, glm::mat4 modelSpace) -> glm::mat4
		{
			glm::mat4 view = glm::lookAt(camera::position, camera::position + camera::front, camera::up);
			glm::mat4 projection = glm::perspective(glm::radians(camera::fov), aspectRatio, 0.1f, editor_mode ? 100.0f : render_distance);
			return projection * view * modelSpace;
		}
	};
}