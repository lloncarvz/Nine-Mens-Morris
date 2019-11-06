#include "Board.h"
#include "Constants.h"

using namespace std;

Board::Board()
{
	board = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
	playerPieces = { 0,0 };
	playerPiecesRemaining = { numberOfPieces,numberOfPieces };
}

bool Board::checkSameColor(const int& a, const int& b, const int& c)
{
	bool ifSameColor = false;
	if (a != -1 && b != -1 && c != -1)
	{
		if (board[a] == board[b] && board[a] == board[c])
			ifSameColor = true;
	}
	return ifSameColor;
}

bool Board::checkMill(const int& position)
{
	bool ifMill = false;
	for (auto& item : ROW_MILLS)
	{
		for (int i = 0; i < 3; i++)
		{
			if (item[i] == position)
			{
				if (checkSameColor(item[0], item[1], item[2]))
					ifMill = true;
			}
		}
	}
	for (auto& item : COLUMN_MILLS)
	{
		for (int i = 0; i < 3; i++)
		{
			if (item[i] == position)
			{
				if (checkSameColor(item[0], item[1], item[2]))
					ifMill = true;
			}
		}
	}
	return ifMill;
}

bool Board::checkMovable(const int& position)
{
	bool ifMove = false;
	for (auto& item : NEIGHBOURS[position])
	{
		if (board[item] == -1)
			ifMove = true;
	}
	return ifMove;
}

vector<int> Board::returnMillablePieces(const int& playerTurn)
{
	vector<int> millable, mills;
	bool turn = !(bool)playerTurn;
	for (int i = 0; i < 24; i++)
	{
		if ((int)turn == board[i])
		{
			if (checkMill(i))
			{
				if (!(find(mills.begin(), mills.end(), i) != mills.end()))
					mills.push_back(i);
			}
			else
			{
				if (!(find(millable.begin(), millable.end(), i) != millable.end()))
					millable.push_back(i);
			}
		}
	}
	if (millable.size() != 0)
		return millable;
	else
		return mills;
}

vector<int> Board::getEmptySpots()
{
	vector<int> emptySpots;
	for (int i = 0; i < 24; i++)
	{
		if (board[i] == -1)
			emptySpots.push_back(i);
	}
	return emptySpots;
}

vector<int> Board::returnMovableSpots(const int& position, const int& numberOfPieces)
{
	vector<int> movableSpots;
	if (numberOfPieces == 3)
	{
		movableSpots = getEmptySpots();
	}
	else
	{
		for (auto& item : NEIGHBOURS[position])
		{
			if (board[item] == -1)
			{
				movableSpots.push_back(item);
			}
		}
	}	
	return movableSpots;
}

void Board::resetBoard()
{
	board = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
	playerPieces = { 0,0 };
	playerPiecesRemaining = { numberOfPieces,numberOfPieces };
}