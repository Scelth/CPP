#include "Game.h"
#include <fstream>

namespace Doom2D
{
	short NUM_ENEMIES;

	// Function to restart the game
	void RestartGame(Game& game)
	{
		CreateEnemies(game);
		CreateObstacles(game);

		InitBackground(game.background, game);
		InitPlayer(game.player, game);

		for (auto& item : game.enemy)
		{
			SetEnemyPosition(item.second, GetRandomPosition(SCREEN_WIDTH, SCREEN_HEIGTH));
		}

		for (auto& item : game.obstacle)
		{
			SetObstaclePosition(item.second, GetRandomPosition(SCREEN_WIDTH, SCREEN_HEIGTH));
		}

		InitText(game.text);
		InitSound(game.sound);

		game.numKilledEnemies = 0;
		game.isGameFinished = false;
		game.gameFinishTime = 0;
	}

	void InitGame(Game& game)
	{
		// Textures
		game.backgroundTexture.loadFromFile(RESOURCES_PATH + "Assets/Hell.png");
		game.playerTexture.loadFromFile(RESOURCES_PATH + "Assets/Doom.png");
		game.enemyTexture.loadFromFile(RESOURCES_PATH + "Assets/Enemy.png");
		game.obstacleTexture.loadFromFile(RESOURCES_PATH + "Assets/Fire.png");

		for (auto& item : game.obstacle)
		{
			InitObstacle(item.second, game);
		}

		RestartGame(game);
	}

	void GameFinished(Game& game, float lastTime)
	{
		game.isGameFinished = true;
		game.gameFinishTime = lastTime;
	}

	void UpdateGame(Game& game, float deltaTime, float lastTime, sf::RenderWindow& window)
	{
		if (!game.isGameFinished)
		{
			UpdatePlayer(game.player, deltaTime);

			// Conditions so that if the player goes outside the window (1920 x 1080), the game restarts
			if (game.player.playerPosition.X - PLAYER_SIZE / 2.f < 0.f || game.player.playerPosition.X + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
				game.player.playerPosition.Y - PLAYER_SIZE / 2.f < 0.f || game.player.playerPosition.Y + PLAYER_SIZE / 2.f > SCREEN_HEIGTH)
			{
				GameFinished(game, lastTime);
			}

			// A loop to create a collision of enemies
			for (auto& item : game.enemy)
			{
				if (IsRectangleCircleCollide(game.player.playerPosition, PLAYER_SIZE, item.second.enemyPosition, ENEMY_SIZE))
				{
					std::ofstream logFile("log.txt", std::ios_base::app); // Open the log file in append mode

					if (game.gameSettings.choice & (1 << 0))
					{
						if (item.second.isAlive)
						{
							item.second.isAlive = false;
							SetEnemyPosition(item.second, GetRandomPosition(SCREEN_WIDTH, SCREEN_HEIGTH));
							game.numKilledEnemies++;
						}
					}

					else if (game.gameSettings.choice & (1 << 1))
					{
						SetEnemyPosition(item.second, GetRandomPosition(SCREEN_WIDTH, SCREEN_HEIGTH));
						game.numKilledEnemies++;
					}

					if (game.gameSettings.choice & (1 << 2))
					{
						if (GetPlayerSpeed(game.player) < 1000)
						{
							SetPlayerSpeed(game.player, GetPlayerSpeed(game.player) + ACCELERATION);
							logFile << "Player Speed: " << GetPlayerSpeed(game.player) << "\n";
						}
					}

					else if (game.gameSettings.choice & (1 << 3))
					{
						SetPlayerSpeed(game.player, GetPlayerSpeed(game.player));
					}

					game.sound.shotSound.play();
				}

				game.text.scoreText.setString("Demons killed: " + std::to_string(game.numKilledEnemies));
			}

			// A cycle for creating a collision of obstacles
			for (auto& item : game.obstacle)
			{
				if (IsRectangleCircleCollide(game.player.playerPosition, PLAYER_SIZE, item.second.obstaclePosition, OBSTACLE_SIZE))
				{
					GameFinished(game, lastTime);
				}
			}
		}

		else
		{
			GetGameScore(game, game.text, window, "GameOver");

			if (lastTime - game.gameFinishTime <= PAUSE_LENGTH)
			{
				game.sound.backgroundMusic.stop();
				game.sound.gameOverSound.play();

				while (game.sound.gameOverSound.getStatus() == sf::Sound::Playing)
				{
					sf::sleep(sf::milliseconds(15));
				}
			}

			else
			{
				// Calling the game restart function
				RestartGame(game);
				game.isGameFinished = false;
			}
		}
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		window.draw(game.background.backgroundSprite);
		game.text.inputHintText.setPosition(window.getSize().x - 450.f, 10.f);
		DrawPlayer(game.player, window);

		for (auto& item : game.enemy)
		{
			if (game.gameSettings.choice & (1 << 0))
			{
				if (item.second.isAlive)
				{
					DrawEnemy(item.second, window);
				}
			}

			else if (game.gameSettings.choice & (1 << 1))
			{
				DrawEnemy(item.second, window);
			}
		}

		if ((game.numKilledEnemies == NUM_ENEMIES) && (game.gameSettings.choice & (1 << 0)))
		{
			GetGameScore(game, game.text, window, "YouWin");

			game.sound.backgroundMusic.stop();
			game.sound.youWinSound.play();

			while (game.sound.youWinSound.getStatus() == sf::Sound::Playing)
			{
				sf::sleep(sf::milliseconds(15));
			}

			RestartGame(game);
		}

		for (auto& item : game.obstacle)
		{
			DrawObstacle(item.second, window);
		}

		window.draw(game.text.scoreText);
		window.draw(game.text.inputHintText);
	}

	void HandleWindowEvents(Game& game, sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close the window when clicking on the X or ESC
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
			{
				//ChangeSetting(game.gameSettings, game, window);
				window.close();
			}
		}
	}
}