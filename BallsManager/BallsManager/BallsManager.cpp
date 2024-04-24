#include <iostream>
using namespace std;

const int NUM_BALLS = 20;

int main()
{
	int balls[NUM_BALLS];
	for (int& ball : balls)
	{
		ball = 0;
	}

	bool shouldContinue = true;

	while (shouldContinue)
	{
		cout << "\nList of commands:" << endl;
		cout << "0 - Exit" << endl;
		cout << "1 - Add ball" << endl;
		cout << "2 - Remove ball" << endl;
		cout << "3 - Count balls" << endl;
		cout << "4 - Total balls" << endl;
		cout << "5 - Needed balls" << endl;
		cout << ">: ";
		string command;
		cin >> command;

		if (command == "1")
		{
			cout << "\nEnter article: ";
			int article = -1;
			cin >> article;

			if (article < 0 || article > NUM_BALLS - 1)
			{
				cout << "Incorrect article!" << endl;
			}

			else
			{
				cout << "There are " << balls[article] << " balls of article " << article << endl;
				cout << "How many balls do you want to add to the article " << article << "?" << endl;
				int count;
				cin >> count;
				balls[article] += count;
				cout << "There are " << balls[article] << " balls of article " << article << " now." << endl;
			}
		}

		else if (command == "2")
		{
			cout << "\nEnter article: ";
			int article = -1;
			cin >> article;

			if (article < 0 || article > NUM_BALLS - 1)
			{
				cout << "Incorrect article!" << endl;
			}

			else
			{
				cout << "There are " << balls[article] << " balls of article " << article << endl;
				cout << "How many balls do you want to remove to the article " << article << "?" << endl;
				int count;
				cin >> count;
				balls[article] -= count;
				cout << "There are " << balls[article] << " balls of article " << article << " now." << endl;
			}
		}

		else if (command == "3")
		{
			cout << "\nEnter article: ";
			int article = -1;
			cin >> article;

			if (article < 0 || article > NUM_BALLS - 1)
			{
				cout << "Incorrect article!" << endl;
			}

			else
			{
				cout << "There are " << balls[article] << " balls of article " << article << endl;
			}
		}

		else if (command == "4")
		{
			int totalBallsCount = 0;

			for (int i = 0; i < NUM_BALLS; ++i)
			{
				totalBallsCount += balls[i];
			}

			cout << "\nThe total number of balls is equal to " << totalBallsCount << endl;
		}

		else if (command == "5")
		{
			for (int i = 0; i < NUM_BALLS; ++i)
			{
				if (balls[i] == 0)
				{
					cout << "There are no balls of article " << i << endl;
				}
			}
		}

		else if (command == "0")
		{
			cout << "\nBye! Have a good time!" << endl;
			break;
		}

		else
		{
			cout << "Unknown command " << command << endl;
		}
	}
}