#include "Game.h"
#include "Score.h"

namespace Doom2D
{
	void GetGameScore(Game& game, GameText& text, sf::RenderWindow& window, std::string situation)
	{
		if (situation == "GameOver")
		{
			window.draw(text.gameOverText);
		}

		else if (situation == "YouWin")
		{
			window.draw(text.youWinText);
		}

		text.totalScoreText.setString("Demons killed: " + std::to_string(game.numKilledEnemies));
        UpdatePlayerScore(game.gameScore, game);
        DisplayRecordTable(text, game.gameScore, game, window);
		window.draw(text.totalScoreText);
		window.display();
	}

    void GenerateRecordTable(GameScore& gameScore, Game& game)
    {
        if (game.gameSettings.choice & (1 << 0))
        {
            gameScore.recordTable =
            {
                {"Player1", rand() % 20 + 1},
                {"Player2", rand() % 20 + 1},
                {"Player3", rand() % 20 + 1},
                {"Player4", rand() % 20 + 1},
                {"Player5", rand() % 20 + 1}
            };
        }

        else if (game.gameSettings.choice & (1 << 1))
        {
            gameScore.recordTable =
            {
                {"Player1", rand()},
                {"Player2", rand()},
                {"Player3", rand()},
                {"Player4", rand()},
                {"Player5", rand()}
            };
        }
    }

    void DisplayRecordTable(GameText& text, GameScore& gameScore, Game& game, sf::RenderWindow& window)
    {
        if (game.gameSettings.choice & (1 << 4))
        {
            std::string recordString;
            std::multimap<int, std::string, std::greater<int>> scoreMap;

            for (const auto& item : gameScore.recordTable)
            {
                scoreMap.insert(std::make_pair(item.second, item.first));
            }

            if (game.gameSettings.choice & (1 << 0))
            {
                recordString = "Records with a finite number of enemies:\n";
            }

            else if (game.gameSettings.choice & (1 << 1))
            {
                recordString = "Records with an infinite number of enemies:\n";
            }

            for (const auto& item : scoreMap)
            {
                recordString += item.second + ": " + std::to_string(item.first) + "\n";
            }

            text.recordText.setString(recordString);
            window.draw(text.recordText);
        }
    }

    void UpdatePlayerScore(GameScore& gameScore, Game& game)
    {
        if ((gameScore.yourScore < game.numKilledEnemies) || gameScore.yourScore == 0)
        {
            gameScore.yourScore = game.numKilledEnemies;
        }

        gameScore.recordTable["You"] = gameScore.yourScore;
    }
}