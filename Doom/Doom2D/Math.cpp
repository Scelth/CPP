#include "Math.h"
#include <SFML/Graphics.hpp>

namespace Doom2D
{
	bool IsRectangleCircleCollide(Position2D rectanglePosition, float playerSize, Position2D circlePosition, float circleSize)
	{
		// Find the nearest point on the rectangle to the center of the circle
		const float closestX = std::max(rectanglePosition.X - (playerSize / 2.f), std::min(circlePosition.X, rectanglePosition.X + (playerSize / 2.f)));
		const float closestY = std::max(rectanglePosition.Y - (playerSize / 2.f), std::min(circlePosition.Y, rectanglePosition.Y + (playerSize / 2.f)));

		// Calculate the distance between the center of the circle and the nearest point on the rectangle
		const float distanceX = circlePosition.X - closestX;
		const float distanceY = circlePosition.Y - closestY;

		// Check if the circle and rectangle intersect
		const float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
		const float circleRadius = (circleSize / 2.f) * (circleSize / 2.f);

		return distanceSquared <= circleRadius;
	}

	Position2D GetRandomPosition(float screenWidth, float screenHeight)
	{
		Position2D result;

		result.X = rand() / (float)RAND_MAX * screenWidth;
		result.Y = rand() / (float)RAND_MAX * screenHeight;

		return result;
	}

	short GetRandomEnemies(short maxEnemies)
	{
		return rand() % (maxEnemies + 1);
	}

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteReact = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidth / spriteReact.width, desiredHeight / spriteReact.height };
		sprite.setScale(scale);
	}

	void SetSpriteOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}

	//void CalcRecord(Game& game)
	//{
	//	if ((game.gameScore.playerScore < game.numKilledEnemies) || game.gameScore.playerScore == 0)
	//	{
	//		game.gameScore.playerScore = game.numKilledEnemies;
	//	}
	//}
}