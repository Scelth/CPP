#include "Settings.h"
#include "Game.h"

namespace Doom2D
{
	void InitSettings(GameSettings& gameSettings, Game& game, sf::RenderWindow& window)
	{
		InitSettingsText(game.text);
		InitSettingsSound(game.sound);
		InitSettingsBackground(game.background);

		while (gameSettings.isSettingsChosen)
		{
			window.clear();
			window.draw(game.backgroundColor);
			window.draw(game.text.settingText);
			window.display();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				if (gameSettings.choice & (1 << 1))
				{
					game.sound.denySound.play();
				}

				else
				{
					gameSettings.choice |= 1 << 0;
					game.sound.settingsSound.play();
				}
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				if (gameSettings.choice & (1 << 0))
				{
					game.sound.denySound.play();
				}

				else
				{
					gameSettings.choice |= 1 << 1;
					game.sound.settingsSound.play();
				}
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{
				if (gameSettings.choice & (1 << 3))
				{
					game.sound.denySound.play();
				}

				else
				{
					gameSettings.choice |= 1 << 2;
					game.sound.settingsSound.play();
				}
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
			{
				if (gameSettings.choice & (1 << 2))
				{
					game.sound.denySound.play();
				}

				else
				{
					gameSettings.choice |= 1 << 3;
					game.sound.settingsSound.play();
				}
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
			{
				gameSettings.choice |= 1 << 4;
				game.sound.settingsSound.play();
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
			{
				if (gameSettings.choice != 5 &&
					gameSettings.choice != 6 &&
					gameSettings.choice != 9 &&
					gameSettings.choice != 10 &&
					gameSettings.choice != 21 &&
					gameSettings.choice != 22 &&
					gameSettings.choice != 25 &&
					gameSettings.choice != 26)
				{
					game.sound.denySound.play();
				}

				else
				{
					if (gameSettings.choice & (1 << 4))
					{
						GenerateRecordTable(game.gameScore, game);
					}

					gameSettings.isSettingsChosen = false;
				}
			}

			else
			{
				HandleWindowEvents(game, window);
			}
		}
	}
}