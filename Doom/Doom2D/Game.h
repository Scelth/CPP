#pragma once
#include "Constants.h"
#include "Background.h"
#include "Player.h"
#include "Enemy.h"
#include "Obstacle.h"
#include "Text.h"
#include "Sound.h"
#include "Settings.h"
#include "Score.h"
#include <unordered_map>

namespace Doom2D
{
	struct Game
	{
		Player player;
		Background background;
		std::unordered_map<int, Enemy> enemy;
		std::unordered_map<int, Obstacle> obstacle;
		//Obstacle obstacle[NUM_OBSTACLES];
		GameText text;
		GameSound sound;
		GameSettings gameSettings;
		GameScore gameScore;

		sf::RectangleShape backgroundColor;

		sf::Texture backgroundTexture;
		sf::Texture playerTexture;
		sf::Texture enemyTexture;
		sf::Texture obstacleTexture;

		int numKilledEnemies = 0;
		bool isGameFinished = false;
		float gameFinishTime = 0.f;
		float restartTimer = 0.f;
	};

	void RestartGame(Game& game);
	void InitGame(Game& game);
	void GameFinished(Game& game, float lastTime);
	void UpdateGame(Game& game, float deltaTime, float lastTime, sf::RenderWindow& window);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void HandleWindowEvents(Game& game, sf::RenderWindow& window);
}