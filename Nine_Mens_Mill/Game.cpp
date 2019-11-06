#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "Constants.h"
#include "Graphics.h"
#include "Board.h"
#include "Game.h"

using namespace sf;
using namespace std;


void resetGame(Board& board, Graphics& graphics, int& gameState, int& gameOverState, int& playerTurn, bool& milling)
{
	board.resetBoard();
	graphics.resetGraphics();
	gameState = 1;
	playerTurn = 0;
	gameOverState = -1;
	milling = false;
}

void placingState(Board& board, Graphics& graphics, const int& posValue, int& playerTurn, int& gameState, bool& milling)
{
	if (posValue != -1)
	{
		int boardValue = board.board[posValue];
		if (boardValue == -1)
		{
			board.board[posValue] = playerTurn;
			board.playerPiecesRemaining[playerTurn]--;
			board.playerPieces[playerTurn]++;

			if (board.checkMill(posValue))
			{
				milling = true;
				vector<int> vectorTmp = board.returnMillablePieces(playerTurn);
				graphics.markers = vectorTmp;
			}

			int p = board.playerPiecesRemaining[playerTurn];

			Sprite sprite;

			if (playerTurn)
			{
				sprite = graphics.getBlackSprite();
				graphics.displayString = "Player 1: Place a white piece!";
				graphics.blackString = to_string(p);
				if(milling)
					graphics.displayString = "Player 2: Remove a white piece!";
			}				
			else
			{
				sprite = graphics.getWhiteSprite();
				graphics.displayString = "Player 2: Place a black piece!";
				graphics.whiteString = to_string(p);
				if (milling)
					graphics.displayString = "Player 1: Remove a black piece!";
			}
			if(milling)
				graphics.setTextColor(!playerTurn);
			else
				graphics.setTextColor(playerTurn);
			int x = (int)graphics.getCoordinates(posValue).x;
			int y = (int)graphics.getCoordinates(posValue).y;
			sprite.setPosition(float(x), float(y));
			graphics.boardPieces[posValue] = sprite;

			playerTurn = !playerTurn;

			if (board.playerPiecesRemaining[1] == 0)
			{
				gameState = 2;
				graphics.displayString = "Player1: Move a white piece!";
				graphics.getDisplayText().setString(graphics.displayString);
				scoreString(graphics, board);
			}
		}
	}
}
void millingState(Board& board, Graphics& graphics, const int& posValue, int playerTurn, int& gameState, bool& milling)
{
	auto iterator = find(graphics.markers.begin(), graphics.markers.end(), posValue);
	if (iterator != graphics.markers.end())
	{
		int index = distance(graphics.markers.begin(), iterator);
		graphics.markers.clear();
		graphics.boardPieces.erase(posValue);
		board.board[posValue] = -1;

		board.playerPieces[playerTurn]--;

		milling = !milling;

		if (gameState == 1)
		{
			if(playerTurn)
				graphics.displayString = "Player 2: Place a black piece!";
			else
				graphics.displayString = "Player 1: Place a white piece!";
		}
		else
		{
			if (playerTurn)
				graphics.displayString = "Player 2: Move a black piece!";
			else
				graphics.displayString = "Player 1: Move a white piece!";
			scoreString(graphics, board);
		}
		graphics.setTextColor(!playerTurn);		
	}
}
void movingState(Board& board, Graphics& graphics, const int& posValue, int& playerTurn, int& gameState, bool& milling, RenderWindow& window)
{
	if (board.board[posValue] == playerTurn && (board.checkMovable(posValue) || board.playerPieces[playerTurn] == 3))
	{
		graphics.markers.clear();
		graphics.selectedToMove = posValue;

		vector<int> vectorTmp = board.returnMovableSpots(posValue, board.playerPieces[playerTurn]);
		graphics.markers = vectorTmp;
	}

	if (find(graphics.markers.begin(), graphics.markers.end(), posValue) != graphics.markers.end())
	{
		int selected = graphics.selectedToMove;
		graphics.markers.clear();
		board.board[selected] = -1;
		board.board[posValue] = playerTurn;
		graphics.boardPieces[posValue] = graphics.boardPieces[selected];
		graphics.boardPieces.erase(selected);

		///// animation /////
		for (int i = 0; i < 500; i++)
		{
			Vector2f vectorTmp = graphics.getCoordinates(posValue) - graphics.getCoordinates(selected);
			graphics.boardPieces[posValue].move(vectorTmp.x / 500, vectorTmp.y / 500);
			window.draw(graphics.getBackgroundSprite());
			graphics.drawPieces(window);
			window.display();
		}

		if (board.checkMill(posValue))
		{
			milling = true;
			vector<int> vectorTmp = board.returnMillablePieces(playerTurn);
			graphics.markers = vectorTmp;
			if(playerTurn)
				graphics.displayString = "Player 2: Remove a white piece!";
			else
				graphics.displayString = "Player 1: Remove a black piece!";
		}
		else
		{
			if (playerTurn)
			{
				graphics.displayString = "Player 1: Move a white piece!";
			}				
			else
			{
				graphics.displayString = "Player 2: Move a black piece!";
			}				
		}
		playerTurn = !playerTurn;
		if (milling)
			graphics.setTextColor(playerTurn);
		else
			graphics.setTextColor(!playerTurn);
	}
}

void scoreString(Graphics& graphics, Board& board)
{
	graphics.whiteString = to_string(board.playerPieces[0]);
	graphics.blackString = to_string(board.playerPieces[1]);
}

void gameOver(Board& board, Graphics& graphics,int& gameOverState)
{
	int p1moves = 0, p2moves = 0;

	int p1RemainingPieces = board.playerPiecesRemaining[0];
	int p2RemainingPieces = board.playerPiecesRemaining[1];

	if (board.playerPieces[0] + p1RemainingPieces == 2)
		gameOverState = 1;
	else if (board.playerPieces[1] + p2RemainingPieces == 2)
		gameOverState = 0;

	for (int i = 0; i < 24; i++)
	{
		if (board.board[i] != -1)
		{
			int pRemainingPieces = board.playerPiecesRemaining[board.board[i]];
			vector<int> vectorTmp = board.returnMovableSpots(i, pRemainingPieces);
			if (!vectorTmp.empty())
			{
				if (board.board[i] == 0)
					p1moves++;
				else
					p2moves++;
			}		
		}
	}
	if (p1moves == 0)
		gameOverState = 1;
	else if (p2moves == 0)
		gameOverState = 0;

	if (gameOverState != -1)
	{
		if (gameOverState == 0)
			graphics.displayString = "Player 1 has won! Press space to restart.";
		else
			graphics.displayString = "Player 2 has won! Press space to restart.";
		graphics.setTextColor(!gameOverState);
	}
}


int main()
{
	RenderWindow window(VideoMode(600, 800), "Nine Men's Morris", Style::Close);
	Graphics graphics;
	Board board;

	int gameState = 1, playerTurn = 0, gameOverState = -1;
	bool milling = false;


	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == Event::Closed)
				window.close();
			
			
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Space)
				{
					resetGame(board, graphics, gameState, gameOverState, playerTurn, milling);
				}
			}


			///// handling game states /////
			if (gameOverState == -1)
			{
				if (event.type == Event::MouseButtonPressed)
				{
					Vector2f position = Vector2f(Mouse::getPosition(window));
					int positionValue = graphics.getClickValue(position);

					if (positionValue != -1)
					{
						if (milling)
						{
							millingState(board, graphics, positionValue, playerTurn, gameState, milling);
							gameOver(board, graphics, gameOverState);
						}
						else if (gameState == 1)
						{
							placingState(board, graphics, positionValue, playerTurn, gameState, milling);
						}
						else if (gameState == 2)
						{
							movingState(board, graphics, positionValue, playerTurn, gameState, milling, window);
							gameOver(board, graphics, gameOverState);
						}
					}	
				}				
			}
		}
		graphics.drawGraphics(window);
	}

	return 0;
}


