#pragma once
#include "Constants.h"
#include "SFML/Graphics.hpp"

namespace Doom2D
{
	struct Game;

	struct GameSettings
	{
		short int choice = 0;
		bool isSettingsChosen = true;
	};

	void InitSettings(GameSettings& gameSettings, Game& game, sf::RenderWindow& window);
	//void ChangeSetting(GameSettings& gameSettings, Game& game, sf::RenderWindow& window);
}