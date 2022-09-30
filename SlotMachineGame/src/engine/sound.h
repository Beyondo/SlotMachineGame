#pragma once
// Я отказываюсь от кроссплатформенности. Это всего лишь задание на собеседование.
#include <SFML/Audio.hpp>
#include <string>
#ifdef min
#undef min
#undef max
#endif
#include <deque>
namespace oct
{
	class sound
	{
		static inline sf::SoundBuffer s_buffer;
		static inline sf::Sound s_sound;
	public:
		sound(const sound&) = delete;
		static inline void load_sound(const std::string& wavFile)
		{
			if (!s_buffer.loadFromFile(wavFile))
				throw std::exception(("Failed to play " + wavFile).c_str());
		}
		static inline void play_sound(float pitch = 1.0f, float volume = 100.0f)
		{
			s_sound.setPitch(pitch);
			s_sound.setVolume(volume);
			s_sound.setBuffer(s_buffer);
			s_sound.play();
		}
		static inline void play_music(const std::string& musicFile, float pitch = 1.0f, float volume = 100.0f)
		{
			static sf::Music s_music;
			s_music.setPitch(pitch);
			s_music.setVolume(volume);
			if (!s_music.openFromFile(musicFile))
				throw std::exception(("Failed to play " + musicFile).c_str());
			s_music.play();
		}
	};
}