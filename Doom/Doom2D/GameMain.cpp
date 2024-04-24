#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Enemy.h"
#include "Obstacle.h"
#include "Background.h"
#include "Text.h"
#include "Sound.h"
#include "Game.h"
#include "Settings.h"
#include "Score.h"

int main()
{
	using namespace Doom2D;

	int seed = (int)time(nullptr);
	srand(seed);

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGTH), "Doom!");

	Game game;

	InitSettings(game.gameSettings, game, window);

	InitGame(game);

	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
		HandleWindowEvents(game, window);

		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		UpdateGame(game, deltaTime, lastTime, window);

		window.clear();
		DrawGame(game, window);
		window.display();
	}

	//DeallocateEnemies(game.enemy);

	return 0;
}