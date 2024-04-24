#pragma once
#include <string>
#include "Text.h"
#include "SFML/Graphics.hpp"
#include <unordered_map>

namespace Doom2D
{
	struct Game;

	struct GameScore
	{
		short yourScore = 0;
		std::unordered_map<std::string, int> recordTable;
	};

	void GetGameScore(Game& game, GameText& text, sf::RenderWindow& window, std::string situation);
	void GenerateRecordTable(GameScore& gameScore, Game& game);
	void DisplayRecordTable(GameText& text, GameScore& gameScore, Game& game, sf::RenderWindow& window);
	void UpdatePlayerScore(GameScore& gameScore, Game& game);
}