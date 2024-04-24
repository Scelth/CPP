#include "Text.h"

namespace Doom2D
{
	void InitText(GameText& text)
	{
		text.scoreText.setFont(text.font);
		text.scoreText.setCharacterSize(24);
		text.scoreText.setFillColor(sf::Color::Yellow);
		text.scoreText.setPosition(10.f, 10.f);

		text.totalScoreText.setFont(text.font);
		text.totalScoreText.setCharacterSize(30);
		text.totalScoreText.setFillColor(sf::Color::White);
		text.totalScoreText.setPosition(SCREEN_WIDTH / 2.5f, SCREEN_HEIGTH / 2.f);

		text.inputHintText.setFont(text.font);
		text.inputHintText.setCharacterSize(24);
		text.inputHintText.setFillColor(sf::Color::Red);
		text.inputHintText.setString("Use WASD keys to move, ESC to exit");

		text.gameOverText.setFont(text.font);
		text.gameOverText.setCharacterSize(50);
		text.gameOverText.setFillColor(sf::Color::White);
		text.gameOverText.setString("GAME OVER");
		text.gameOverText.setPosition(SCREEN_WIDTH / 2.5f, SCREEN_HEIGTH / 2.5f);

		text.youWinText.setFont(text.font);
		text.youWinText.setCharacterSize(50);
		text.youWinText.setFillColor(sf::Color::White);
		text.youWinText.setString("YOU WIN!");
		text.youWinText.setPosition(SCREEN_WIDTH / 2.5f, SCREEN_HEIGTH / 2.5f);

		text.recordText.setFont(text.font);
		text.recordText.setCharacterSize(50);
		text.recordText.setFillColor(sf::Color::White);
		text.recordText.setPosition(SCREEN_WIDTH / 5.f, SCREEN_HEIGTH / 3.f);
	}

	void InitSettingsText(GameText& text)
	{
		text.font.loadFromFile(RESOURCES_PATH + "Fonts/Linepixels.ttf");

		text.settingText.setFont(text.font);
		text.settingText.setCharacterSize(30);
		text.settingText.setFillColor(sf::Color::White);
		text.settingText.setString("SELECT SETTINGS \n\nChoose two or three options \n1 - With finite number of enemies. \n2 - With infinite number of enemies. \n3 - With player acceleration. \n4 - Without player acceleration. \n5 - Show record table. \n0 - Exit the settings. \n\nESC - Exit the game.");
		text.settingText.setPosition(SCREEN_WIDTH / 2.5f, SCREEN_HEIGTH / 2.5f);
	}

	void InitPauseText(GameText& text)
	{
		text.font.loadFromFile(RESOURCES_PATH + "Fonts/Linepixels.ttf");

		text.pauseText.setFont(text.font);
		text.pauseText.setCharacterSize(30);
		text.pauseText.setFillColor(sf::Color::White);
		text.pauseText.setString("");
		text.pauseText.setPosition(SCREEN_WIDTH / 2.5f, SCREEN_HEIGTH / 2.5f);
	}
}