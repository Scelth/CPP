#pragma once
#include "Constants.h"
#include "Math.h"

namespace Doom2D
{
	struct Game;

	struct Obstacle
	{
		Position2D obstaclePosition;
		sf::Sprite obstacleSprite;
	};

	void InitObstacle(Obstacle& obstacle, const Game& game);
	void SetObstaclePosition(Obstacle& obstacle, const Position2D& position);
	void DrawObstacle(Obstacle& obstacle, sf::RenderWindow& window);
	void CreateObstacles(Game& game);
}