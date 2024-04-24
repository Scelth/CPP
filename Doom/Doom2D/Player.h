#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace Doom2D
{
	struct Game;

	enum class PlayerDirection
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	struct Player
	{
		Position2D playerPosition;
		float playerSpeed = INITIAL_SPEED;
		PlayerDirection playerDirection = PlayerDirection::Right;
		sf::Sprite playerSprite;
	};

	void InitPlayer(Player& player, const Game& game);
	void SetPlayerSpeed(Player& player, float speed);
	float GetPlayerSpeed(const Player& player);
	void UpdatePlayer(Player& player, float deltaTime);
	void DrawPlayer(Player& player, sf::RenderWindow& window);
}