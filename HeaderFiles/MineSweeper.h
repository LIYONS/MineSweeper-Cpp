#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
#include<cstdlib>

#define BOMB '*'
#define EMPTY ' '

enum Status
{
	visited,
	notVisited
};
class Element
{
public:
	char data;
	Status status;
};


class MineSweeper
{
public:
	int n = 9;
	int bombs = 10;
	Element board[9][9];
	Element userBoard[9][9];
	bool isGameOver;

	MineSweeper();
	void PlaceBombs(int x, int y);
	void WinCheck();
	void RevealNeighbours(int i, int j);
	void Reveal(int i, int j);
	bool IsInside(int i, int j);
	int ComputeNeighbours(int i, int j);
	void InitializeBoard();
	void PrintBoard();
	void GameLoop();
	void RevealAllBombs();
};