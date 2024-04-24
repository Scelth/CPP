#include "Sound.h"

namespace Doom2D
{
	void InitSound(GameSound& sound)
	{
		sound.backgroundMusic.openFromFile(RESOURCES_PATH + "Audio/BackgroundMusic.wav");
		sound.backgroundMusic.setLoop(true);

		sound.shotSoundBuffer.loadFromFile(RESOURCES_PATH + "Audio/ShotSound.wav");
		sound.shotSound.setBuffer(sound.shotSoundBuffer);

		sound.gameOverSoundBuffer.loadFromFile(RESOURCES_PATH + "Audio/GameOverSound.wav");
		sound.gameOverSound.setBuffer(sound.gameOverSoundBuffer);

		sound.youWinSoundBuffer.loadFromFile(RESOURCES_PATH + "Audio/YouWinSound.wav");
		sound.youWinSound.setBuffer(sound.youWinSoundBuffer);

		sound.backgroundMusic.play();
	}

	void InitSettingsSound(GameSound& sound)
	{
		sound.settingsSoundBuffer.loadFromFile(RESOURCES_PATH + "Audio/JackpotSound.wav");
		sound.settingsSound.setBuffer(sound.settingsSoundBuffer);

		sound.denySoundBuffer.loadFromFile(RESOURCES_PATH + "Audio/NoSound.wav");
		sound.denySound.setBuffer(sound.denySoundBuffer);
	}
}