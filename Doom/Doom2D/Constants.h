#pragma once
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>

namespace Doom2D
{
	const std::string RESOURCES_PATH = "Resources/";
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGTH = 1080;
	const float INITIAL_SPEED = 100.f;
	const float PLAYER_SIZE = 40.f;
	const float ACCELERATION = 20.f;
	const short MAX_NUM_ENEMIES = 20;
	const float ENEMY_SIZE = 40.f;
	const short NUM_OBSTACLES = 10;
	const float OBSTACLE_SIZE = 40.f;
	const float PAUSE_LENGTH = 3.f;

	extern short NUM_ENEMIES;
}