#include "../HeaderFiles/MineSweeper.h"

MineSweeper::MineSweeper()
{
	int x = 0, y = 0;
	InitializeBoard();
	PrintBoard();
	isGameOver = false;
	do
	{
		std::cout << "\nEnter x\n";
		std::cin >> x;
		std::cout << "\nEnter y\n";
		std::cin >> y;
	} while (x < 1 || x>9 || y < 1 || y>9);

	x--;
	y--;
	PlaceBombs(x, y);
	Reveal(x, y);
	GameLoop();
}

void MineSweeper::RevealAllBombs()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (board[i][j].data == BOMB)
			{
				userBoard[i][j].data = BOMB;
			}
		}
	}
}

void MineSweeper::Reveal(int i, int j)
{
	userBoard[i][j].data = board[i][j].data;
	if (board[i][j].data == BOMB)
	{
		isGameOver = true;
		RevealAllBombs();
		PrintBoard();
		std::cout << "\nOops! You Lose\n";
	}
	if (board[i][j].data == '0')
	{
		RevealNeighbours(i, j);
	}
}

void MineSweeper::RevealNeighbours(int i, int j)
{
	for (int lineOffset = -1; lineOffset <= 1; lineOffset++)
	{
		for (int colOffset = -1; colOffset <= 1; colOffset++)
		{
			int nextLine = i + lineOffset, nextCol = j + colOffset;
			if (IsInside(nextLine, nextCol))
			{
				userBoard[nextLine][nextCol].data = board[nextLine][nextCol].data;
				if (board[nextLine][nextCol].data == '0' && board[nextLine][nextCol].status == notVisited)
				{
					board[nextLine][nextCol].status = visited;
					RevealNeighbours(nextLine, nextCol);
				}
			}
		}
	}
}

void MineSweeper::WinCheck()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (board[i][j].data != BOMB && userBoard[i][j].data != board[i][j].data)
			{
				return;
			}
		}
	}
	isGameOver = true;
	std::cout << "You Won";
}

bool MineSweeper::IsInside(int i, int j)
{
	return i >= 0 && i < n&& j >= 0 && j < n;
}