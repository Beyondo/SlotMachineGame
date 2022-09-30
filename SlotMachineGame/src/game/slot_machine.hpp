#pragma once
#include <game/card.hpp>
#include <game/reel.hpp>
#include <chrono>
namespace oct
{
	class slot_machine : public quad
	{
	public:
		slot_machine()
		{
			reel::rng.seed(static_cast<uint32_t>(time(0)));
			//
			position.z = 0.6f;
			size = glm::vec2(1.5f, 1.0f);
			//
			int x, y, channels;
			stbi_uc* texture_data = stbi_load("assets/images/machine.png", &x, &y, &channels, 4);
			texture = renderer2d::context()->create_texture2d(texture_data, x, y, channels);
			stbi_image_free(texture_data);
			uint32_t id = 0;
			reels[0].next = &reels[1];
			for (int i = 1; i < 5; ++i)
			{
				reel& r = reels[i];
				r.prev = &reels[i - 1];
				if (i < 4) r.next = &reels[i + 1];
			}
		}
		void start()
		{
			this->reels->slotMatches.resize(this->reels->cards.size());
			for(auto& m : this->reels->slotMatches) m = 0;
			this->reels->score = 0;
			for (auto& reel : this->reels)
				reel.spin(1.0f, 1.0f, 2.0f);
			m_startTime = static_cast<float>(glfwGetTime());
		}
		void stop()
		{
			std::vector<uint32_t> slots;
			for (auto& reel : reels)
			{
				std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
				auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch());
				rng.seed(static_cast<uint32_t>(nanoseconds.count()));
				std::uniform_int_distribution<uint32_t> distribution(0, static_cast<uint32_t>(reel.cards.size()) - 1);
				slots.push_back(distribution(rng));
			}
			// A B C B A ---> A B B C D
			std::sort(slots.begin(), slots.end()); // Вы можете прокомментировать это.
			for (int i = 0; i < slots.size(); ++i)
				reels[i].stop(slots[i]);
		}
		bool peak_velocity()
		{
			for (auto& r : reels)
				if (r.velocity.y != r.max_Velocity())
					return false;
			return true;
		}
		bool running()
		{
			for (auto& r : reels)
				if (r.velocity.y > 0)
					return true;
			return false;
		}
		bool is_stopped_or_stopping()
		{
			for (auto& r : reels)
				if (r.angular_velocity() < r.max_Velocity())
					return true;
			return false;
		}
		reel reels[5];
		float win_bias = 0; // 0 = 100% справедливый
	private:
		float m_startTime;
		static inline std::default_random_engine rng{};
		virtual void on_draw() override
		{
			float margin = 0.013020833f; // жестко закодирован из текстуры.
			glm::vec2 reelSize = glm::vec2(size.x * 0.2f, size.y * 0.7f);
			float reel_position_x = this->position.x - this->size.x + reelSize.x + margin;
			float step = reel_position_x / 2.0f;
			for (auto& reel : reels)
			{
				reel.size = glm::vec3(0.23f, 1.00f, this->size.y * 0.6f);
				reel.position = glm::vec3(reel_position_x, 0.13f, 0.01f);
				glm::vec3 borderPosition = glm::vec3(reel.position.x - reel.size.x - margin, reel.position.y, reel.position.z);
				glm::vec2 borderSize = glm::vec2(0.6f, this->size.y);
				//renderer2d::draw_quad_rotated(borderPosition, borderSize, glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(90.0f), glm::vec4(1.0f));
				reel.color = glm::vec4(0);
				renderer2d::draw(&reel);
				reel_position_x -= step;
			}
			if (!is_stopped_or_stopping() && glfwGetTime() - m_startTime > 60.0f)
				stop();
		}
	};
}