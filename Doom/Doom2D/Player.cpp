#include "Player.h"
#include "Game.h"

namespace Doom2D
{
	void InitPlayer(Player& player, const Game& game)
	{
		player.playerPosition = { SCREEN_WIDTH / 2.f, SCREEN_HEIGTH / 2.f };
		SetPlayerSpeed(player, INITIAL_SPEED);
		player.playerDirection = PlayerDirection::Right;

		player.playerSprite.setTexture(game.playerTexture);
		SetSpriteSize(player.playerSprite, PLAYER_SIZE, PLAYER_SIZE);
		SetSpriteOrigin(player.playerSprite, 0.5f, 0.5f);
	}

	void SetPlayerSpeed(Player& player, float speed)
	{
		player.playerSpeed = speed;
	}

	float GetPlayerSpeed(const Player& player)
	{
		return player.playerSpeed;
	}

	void UpdatePlayer(Player& player, float deltaTime)
	{
		// Conditions for linking keys to directions
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player.playerDirection = PlayerDirection::Right;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			player.playerDirection = PlayerDirection::Up;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player.playerDirection = PlayerDirection::Left;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			player.playerDirection = PlayerDirection::Down;
		}


		switch (player.playerDirection)
		{
		case PlayerDirection::Right:
			player.playerPosition.X += player.playerSpeed * deltaTime;
			break;

		case PlayerDirection::Up:
			player.playerPosition.Y -= player.playerSpeed * deltaTime;
			break;

		case PlayerDirection::Left:
			player.playerPosition.X -= player.playerSpeed * deltaTime;
			break;

		case PlayerDirection::Down:
			player.playerPosition.Y += player.playerSpeed * deltaTime;
			break;
		}
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.playerSprite.setPosition(player.playerPosition.X, player.playerPosition.Y);
		window.draw(player.playerSprite);

		if (player.playerDirection == PlayerDirection::Left)
		{
			SetSpriteSize(player.playerSprite, -PLAYER_SIZE, PLAYER_SIZE);
		}

		else
		{
			SetSpriteSize(player.playerSprite, PLAYER_SIZE, PLAYER_SIZE);
		}
	}
}