#pragma once

#include <vector>

class Board
{
private:
	bool checkSameColor(const int& a, const int& b, const int& c);
	std::vector<int> getEmptySpots();

	
	int numberOfPieces = 9;

public:

	std::vector<int> board;
	std::vector<int> playerPieces;
	std::vector<int> playerPiecesRemaining;

	Board();

	void resetBoard();

	bool checkMill(const int& position);
	bool checkMovable(const int& position);
	std::vector<int> returnMillablePieces(const int& playerTurn);
	std::vector<int> returnMovableSpots(const int& position, const int& numberOfPieces);
};

