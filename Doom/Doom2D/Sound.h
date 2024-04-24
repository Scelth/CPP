#pragma once
#include "Constants.h"
#include <SFML/Audio.hpp>

namespace Doom2D
{
	struct GameSound
	{
		sf::SoundBuffer settingsSoundBuffer;
		sf::Sound settingsSound;

		sf::SoundBuffer denySoundBuffer;
		sf::Sound denySound;

		sf::Music backgroundMusic;

		sf::SoundBuffer shotSoundBuffer;
		sf::Sound shotSound;

		sf::SoundBuffer gameOverSoundBuffer;
		sf::Sound gameOverSound;

		sf::SoundBuffer youWinSoundBuffer;
		sf::Sound youWinSound;
	};

	void InitSound(GameSound& sound);
	void InitSettingsSound(GameSound& sound);
}