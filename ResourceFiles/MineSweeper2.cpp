#include "../HeaderFiles/MineSweeper.h"

int MineSweeper::ComputeNeighbours(int i, int j)
{
	int numBombs=0;
	for (int lineOffset = -1; lineOffset <= 1; lineOffset++)
	{
		for (int colOffset = -1; colOffset <= 1; colOffset++)
		{
			int nextLine = i + lineOffset, nextCol = j + colOffset;
			if ( IsInside(nextLine,nextCol) && board[i + lineOffset][j + colOffset].data == BOMB)
			{
				numBombs++;
			}
		}
	}
	return numBombs;
}

void MineSweeper::InitializeBoard()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			board[i][j].data =userBoard[i][j].data=EMPTY;
			board[i][j].status = notVisited;
		}
	}
}

void MineSweeper::PlaceBombs(int x,int y)
{
	std::vector<std::pair<int, int>> positions;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if ((i >= x - 1 && i <= x + 1) && (j >= y - 1 && j <= y + 1))
			{
				continue;
			}
			positions.push_back(std::make_pair(i, j));
		}
	}
	std::random_shuffle(positions.begin(), positions.end());
	for (int i = 0; i <bombs; i++)
	{
		board[positions[i].first][positions[i].second].data=BOMB;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (board[i][j].data != BOMB)
			{
				board[i][j].data = ComputeNeighbours(i, j) + '0';
			}
		}
	}
}

void MineSweeper::PrintBoard()
{
	std::cout << "   ";
	for (int i = 0; i < n; i++)
	{
		std::cout <<" " << i + 1 << "  ";
	}
	std::cout << "\n________________________________________\n";
	std::cout << "\n";
	for (int i = 0; i < n; i++)
	{
		std::cout <<i+1<< " |";
		for (int j = 0; j < n; j++)
		{
			std::cout <<" " << userBoard[i][j].data << " |";
		}
		std::cout << "\n\n";
	}
}

void MineSweeper::GameLoop()
{
	int x = 0,y = 0;
	while (!isGameOver)
	{
		PrintBoard();
		do
		{
			std::cout << "\nEnter x\n";
			std::cin >> x;
			std::cout << "\nEnter y\n";
			std::cin >> y;
		} while (x < 1 || x>9 || y < 1 || y>9);

		x--;
		y--;
		Reveal(x, y);
		WinCheck();
	}
}