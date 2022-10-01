#pragma once
#include <engine/renderer2d.h>
#include <engine/physics.h>
#include <engine/sound.h>
#include <GLFW/glfw3.h>
#include <map>
#include <random>
#include <algorithm>
#define NO_CARD UINT32_MAX
namespace oct
{
	class reel : public ring, public physx::object // velocity.y будет рассматриваться как угловая скорость
	{
	public:
		void spin(float initialRPMAcceleration = 0, float initialRPM = 1.0f, float speedMultiplier = 1.0f)
		{
			this->acceleration.y = (360.0f * initialRPMAcceleration);
			this->m_maxVelocity = (360.0F * initialRPM);
			this->m_speedMultiplier = speedMultiplier;
		}
		void stop(uint32_t id)
		{
			m_targetCard = id;
			m_should_stop_spinning = true;
		}
		void attach_deck(std::vector<card> Cards)
		{
			float step = 360.0f / Cards.size();
			std::shuffle(std::begin(Cards), std::end(Cards), rng);
			float angle = 0.0f;
			for (auto& card : Cards)
			{
				this->cards.insert({ card, angle });
				angle += step;
			}
		}
		auto current_slot()->card
		{
			for (const auto& [c, value] : cards)
				if (c.id() == m_targetCard)
					return c;
			return cards.begin()->first;
		}
		void set_angular_velocity(float angularVelocity) { this->velocity.y = angularVelocity; }
		auto seconds_since_stopped() const -> float { return static_cast<float>(glfwGetTime() - this->m_stop_time); }
		constexpr auto max_Velocity() const -> float { return m_maxVelocity; }
		constexpr auto angular_velocity()const -> float { return this->velocity.y; }
		constexpr bool is_spinning() const { return angular_velocity() != 0; }
	private:
		float normalize(const float value, const float start, const float end)
		{
			const float width = end - start;
			const float offsetValue = value - start;
			return (offsetValue - (floorf(offsetValue / width) * width)) + start;
		}
		//
		using angle_deg = float;
		std::map<card, angle_deg> cards;
		uint32_t m_targetCard = NO_CARD;
		//
		double m_stop_time = 0;
		float m_maxVelocity = 360.0f;
		float m_targetAngle = 0.0f;
		float m_currentAngle = 0.0f;
		float m_speedMultiplier = 1.0f;
		//
		reel* prev = nullptr;
		reel* next = nullptr;
		//
		bool m_stop_issued = false;
		bool m_should_stop_spinning = false;
		template<typename Degrees>
		void set_position_on_reel(glm::vec3& pos, Degrees angularPosition)
		{
			pos.x = this->position.x;
			pos.y = this->position.y + sin(glm::radians(static_cast<float>(angularPosition))) * (this->size.y);
			pos.z = this->position.z + cos(glm::radians(static_cast<float>(angularPosition))) * (this->size.z);
		}
		void set_rotation_angle(float& rot, glm::vec3& rotation_by_position)
		{
			glm::vec3 point = rotation_by_position;
			glm::vec3 direction = this->position - point;
			//glm::vec3 r = rotation_by_position;
			rot = atan2(direction.z, direction.y) + (glm::pi<float>() / 2);
		}
		void draw()
		{
			for (auto& cardAngle : cards)
			{
				card gameCard = cardAngle.first;
				float angle = cardAngle.second;
				gameCard.size = glm::vec2(this->size.x, this->size.x);
				gameCard.rotation = glm::vec3(1.0f, 0, 0);
				set_position_on_reel(gameCard.position, angle - m_currentAngle);
				//set_rotation_angle(card.rotation_angle, card.position); // Проще просто напечатать текстуру на 3D-колесе.
				renderer2d::draw(&gameCard);
			}
		}
		void stop_instantly() // Not realistic (but we could also stop at exactly the card's position)
		{
			float angle = m_targetAngle;
			this->acceleration.y = 0;
			this->set_angular_velocity(0);
			m_currentAngle = angle;
		}
		void stop_with_animation()
		{
			// Единственными решениями для S=ut+½at² являются либо -180, либо бесконечность.
			acceleration.y = -180;
		}
		bool can_stop()
		{
			return this->prev ? !this->prev->is_spinning() && this->prev->seconds_since_stopped() > 1.0f : true;
		}
		virtual void on_integration(float dt) override
		{
			if (m_should_stop_spinning && can_stop())
			{
				auto it = cards.begin();
				std::advance(it, m_targetCard);
				m_targetAngle = it->second;
				float noramlizedm_currentAngle = normalize((m_currentAngle + dt * this->angular_velocity()), 0.0f, 360.0f);
				// Ожидает, пока целевой слот выровняется на 0 градусов
				if (abs(noramlizedm_currentAngle - m_targetAngle) < (360.0f * dt))
				{
					m_currentAngle = m_targetAngle; // Исправляет выравнивание
					stop_with_animation();
					m_should_stop_spinning = false;
					m_stop_issued = true;
				}
			}
			set_angular_velocity(glm::min(m_maxVelocity, angular_velocity() + (acceleration.y * dt * m_speedMultiplier)));
			m_currentAngle += this->angular_velocity() * dt * m_speedMultiplier;
			if (m_stop_issued && abs(this->angular_velocity()) < (1000.0 * dt))
			{
				m_currentAngle = m_targetAngle; // Исправляет выравнивание
				acceleration.y = 0;
				velocity.y = 0;
				m_stop_issued = false;
				uint32_t num_matches = ++this->slotMatches[m_targetCard];
				if (num_matches > 1) ++score;
				sound::play_sound(1 + (score * 0.1f));
				this->color = glm::vec4(1.0f);
				if (next == nullptr) sound::play_music("assets/sounds/win.wav", 1.0f, score * 50.0f);
				m_stop_time = glfwGetTime();
				std::cout << current_slot().name() << std::endl;
			}
		}
		virtual void on_draw() override
		{
			draw();
		}
		//
		static inline std::default_random_engine rng{};
		static inline std::vector<uint32_t> slotMatches;
		static inline uint32_t score = 0;
		//
		friend class slot_machine;
	};
}