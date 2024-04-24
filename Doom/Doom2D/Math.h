#pragma once

namespace sf
{
	class Sprite;
}

namespace Doom2D
{
	struct Vector2D
	{
		float X = 0;
		float Y = 0;
	};

	typedef Vector2D Position2D;

	bool IsRectangleCircleCollide(Position2D rectanglePosition, float playerSize, Position2D circlePosition, float circleRadius);
	Position2D GetRandomPosition(float screenWidth, float screenHeight);
	short GetRandomEnemies(short maxEnemies);
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
	void SetSpriteOrigin(sf::Sprite& sprite, float originX, float originY);
	//void CalcRecord(Game& game);
}