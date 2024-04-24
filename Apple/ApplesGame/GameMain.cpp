// Я изменил игру, добавил звуки, музыку, текстуры. По сути, это та же самая игра яблоки, но в стилистике первого Doom.

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGTH = 1080;
const float INITIAL_SPEED = 100.f;
const float PLAYER_SIZE = 40.f;
const float ACCELIRATION = 20.f;
const int NUM_ENEMIES = 20;
const float ENEMY_SIZE = 40.f;
const int NUM_OBSTACLES = 10;
const float OBSTACLE_SIZE = 40.f;
sf::Font font;

void HandleWindowEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		// Закрыть окно при нажатии на крестик или ESC
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
		{
			window.close();
		}
	}
}

// Функция для перезапуска игры
void ResetGame(float& playerX, float& playerY, float& playerSpeed, int& numKilledEnemies,
	float enemyX[], float enemyY[], sf::Sprite enemySprite[],
	float obstacleX[], float obstacleY[], sf::Sprite obstacleSprite[])
{
	playerX = SCREEN_WIDTH / 2.f;
	playerY = SCREEN_HEIGTH / 2.f;
	playerSpeed = INITIAL_SPEED;
	numKilledEnemies = 0;

	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		enemyX[i] = rand() / (float)RAND_MAX * SCREEN_WIDTH;
		enemyY[i] = rand() / (float)RAND_MAX * SCREEN_HEIGTH;
		enemySprite[i].setPosition(enemyX[i], enemyY[i]);
	}

	for (int i = 0; i < NUM_OBSTACLES; i++)
	{
		obstacleX[i] = rand() / (float)RAND_MAX * SCREEN_WIDTH;
		obstacleY[i] = rand() / (float)RAND_MAX * SCREEN_HEIGTH;
		obstacleSprite[i].setPosition(obstacleX[i], obstacleY[i]);
	}
}

int main()
{
	int seed = (int)time(nullptr);
	srand(seed);

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGTH), "Doom!");

	float playerX = SCREEN_WIDTH / 2.f;
	float playerY = SCREEN_HEIGTH / 2.f;
	float playerSpeed = INITIAL_SPEED;
	int playerDirection = 0;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	backgroundTexture.loadFromFile(RESOURCES_PATH + "Assets/Hell.png");
	backgroundSprite.setTexture(backgroundTexture);

	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	playerTexture.loadFromFile(RESOURCES_PATH + "Assets/DoomGuy.png");
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(PLAYER_SIZE / playerTexture.getSize().x, PLAYER_SIZE / playerTexture.getSize().y);
	playerSprite.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
	playerSprite.setPosition(playerX, playerY);

	sf::Texture enemyTexture;
	enemyTexture.loadFromFile(RESOURCES_PATH + "Assets/Enemy.png");
	sf::Sprite enemySprite[NUM_ENEMIES];
	float enemyX[NUM_ENEMIES];
	float enemyY[NUM_ENEMIES];

	sf::Texture obstacleTexture;
	obstacleTexture.loadFromFile(RESOURCES_PATH + "Assets/Fire.png");
	sf::Sprite obstacleSprite[NUM_OBSTACLES];
	float obstacleX[NUM_OBSTACLES];
	float obstacleY[NUM_OBSTACLES];

	// Шрифт
	font.loadFromFile(RESOURCES_PATH + "Fonts/Linepixels.ttf");

	// Текст
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::Yellow);
	scoreText.setPosition(10.f, 10.f);

	sf::Text inputHintText;
	inputHintText.setFont(font);
	inputHintText.setCharacterSize(24);
	inputHintText.setFillColor(sf::Color::Red);
	inputHintText.setString("Use WASD keys to move, ESC to exit");

	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(50);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setString("GAME OVER");
	gameOverText.setPosition(SCREEN_WIDTH / 2.5f, SCREEN_HEIGTH / 2.5f);

	sf::Music backgroundMusic;
	backgroundMusic.openFromFile(RESOURCES_PATH + "Audio/Background.ogg");
	backgroundMusic.setLoop(true); // Зацикливание аудио

	sf::SoundBuffer shotSoundBuffer;
	shotSoundBuffer.loadFromFile(RESOURCES_PATH + "Audio/Shot.ogg");
	sf::Sound shotSound;
	shotSound.setBuffer(shotSoundBuffer);

	// Цикл координат яблок
	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		enemyX[i] = rand() / (float)RAND_MAX * SCREEN_WIDTH;
		enemyY[i] = rand() / (float)RAND_MAX * SCREEN_HEIGTH;

		enemySprite[i].setTexture(enemyTexture);
		enemySprite[i].setScale(ENEMY_SIZE / enemyTexture.getSize().x, ENEMY_SIZE / enemyTexture.getSize().y);
		enemySprite[i].setOrigin(ENEMY_SIZE / 2.f, ENEMY_SIZE / 2.f);
		enemySprite[i].setPosition(enemyX[i], enemyY[i]);
	}

	// Цикл координат препядсвий
	for (int i = 0; i < NUM_OBSTACLES; i++)
	{
		obstacleX[i] = rand() / (float)RAND_MAX * SCREEN_WIDTH;
		obstacleY[i] = rand() / (float)RAND_MAX * SCREEN_HEIGTH;

		obstacleSprite[i].setTexture(obstacleTexture);
		obstacleSprite[i].setScale(OBSTACLE_SIZE / enemyTexture.getSize().x, OBSTACLE_SIZE / enemyTexture.getSize().y);
		obstacleSprite[i].setOrigin(OBSTACLE_SIZE / 2.f, OBSTACLE_SIZE / 2.f);
		obstacleSprite[i].setPosition(obstacleX[i], obstacleY[i]);
	}

	int numKilledEnemies = 0;

	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	backgroundMusic.play();

	while (window.isOpen())
	{
		HandleWindowEvents(window);

		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Условия для привязки клавиш к направления
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			playerDirection = 0;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			playerDirection = 1;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			playerDirection = 2;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			playerDirection = 3;
		}


		// Условия для направления ускорения
		if (playerDirection == 0)
		{
			playerX += playerSpeed * deltaTime;
		}

		else if (playerDirection == 1)
		{
			playerY -= playerSpeed * deltaTime;
		}

		else if (playerDirection == 2)
		{
			playerX -= playerSpeed * deltaTime;
		}

		else if (playerDirection == 3)
		{
			playerY += playerSpeed * deltaTime;
		}


		// Условия для того, чтобы, если игрок вышел за пределы окна (1920 х 1080), то игра перезапускалась
		if (playerX - PLAYER_SIZE / 5.f < 0.f || playerX + PLAYER_SIZE / 1.2f > SCREEN_WIDTH ||
			playerY - PLAYER_SIZE / 5.f < 0.f || playerY + PLAYER_SIZE / 1.1f > SCREEN_HEIGTH)
		{
			window.draw(gameOverText);
			window.display();
			sf::sleep(sf::milliseconds(600));

			// Вызываем функцию для перезапуска игры
			ResetGame(playerX, playerY, playerSpeed, numKilledEnemies, enemyX, enemyY, enemySprite, obstacleX, obstacleY, obstacleSprite);
			backgroundMusic.stop();
			backgroundMusic.play();
			playerDirection = 0;
		}

		// Цикл для создания коллизии препядсвий
		for (int i = 0; i < NUM_OBSTACLES; i++)
		{
			float squareDistance = (playerX - obstacleX[i]) * (playerX - obstacleX[i]) +
				(playerY - obstacleY[i]) * (playerY - obstacleY[i]);

			float squareRaduisSum = (OBSTACLE_SIZE + PLAYER_SIZE) * (OBSTACLE_SIZE + PLAYER_SIZE) / 4;

			if (squareDistance <= squareRaduisSum)
			{
				window.draw(gameOverText);
				window.display();
				sf::sleep(sf::milliseconds(600));

				// Вызываем функцию для перезапуска игры
				ResetGame(playerX, playerY, playerSpeed, numKilledEnemies, enemyX, enemyY, enemySprite, obstacleX, obstacleY, obstacleSprite);
				backgroundMusic.stop();
				backgroundMusic.play();
				playerDirection = 0;
			}

		}

		// Цикл для создания коллизии яблок
		for (int i = 0; i < NUM_ENEMIES; i++)
		{
			float squareDistance = (playerX - enemyX[i]) * (playerX - enemyX[i]) +
				(playerY - enemyY[i]) * (playerY - enemyY[i]);

			float squareRaduisSum = (ENEMY_SIZE + PLAYER_SIZE) * (ENEMY_SIZE + PLAYER_SIZE) / 4;

			// if изменен так, что теперь игра бесконечная. Яблоки появляются вновь, после съедения
			if (squareDistance <= squareRaduisSum)
			{
				++numKilledEnemies;
				playerSpeed += ACCELIRATION;
				shotSound.play();

				enemyX[i] = rand() / (float)RAND_MAX * SCREEN_WIDTH;
				enemyY[i] = rand() / (float)RAND_MAX * SCREEN_HEIGTH;
			}

			scoreText.setString("Demons killed: " + std::to_string(numKilledEnemies));
		}

		inputHintText.setPosition(window.getSize().x - 450.f, 10.f);

		window.clear();
		window.draw(backgroundSprite);
		playerSprite.setPosition(playerX, playerY);

		for (int i = 0; i < NUM_ENEMIES; i++)
		{
			enemySprite[i].setPosition(enemyX[i], enemyY[i]);
			window.draw(enemySprite[i]);
		}

		for (int i = 0; i < NUM_OBSTACLES; i++)
		{
			window.draw(obstacleSprite[i]);
		}

		window.draw(playerSprite);
		window.draw(scoreText);
		window.draw(inputHintText);
		window.display();
	}

	return 0;
}