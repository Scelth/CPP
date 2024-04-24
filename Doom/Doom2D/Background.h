#pragma once
#include "Constants.h"

namespace Doom2D
{
	struct Game;

	struct Background
	{
		sf::Sprite backgroundSprite;
		sf::RectangleShape backgroundColor;
	};

	void InitBackground(Background& background, const Game& game);
	void InitSettingsBackground(Background& background);
}