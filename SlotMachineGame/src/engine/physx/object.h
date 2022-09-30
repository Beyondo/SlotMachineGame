#pragma once
#include <engine/physx/physx.h>
#include <glm/glm.hpp>
namespace oct
{
	// На данный момент физического движка нет.
	class physx::object
	{
	public:
		glm::vec3 velocity = glm::vec3(0);
		glm::vec3 acceleration = glm::vec3(0);
		inline void integrate(float dt)
		{
			on_integration(dt);
		}
	private:
		virtual void on_integration(float dt) = 0;
	};
}