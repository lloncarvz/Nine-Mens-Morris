#include "Graphics.h"
#include <iostream>
#include <algorithm>

using namespace std;
using namespace sf;

Graphics::Graphics()
{
	selectedToMove = -1;
	displayString = "Player 1: Place a piece!";
	whiteString = "9";
	blackString = "9";
	if (!font.loadFromFile("resources/raleway.ttf")) { cout << "Can't load font." << endl; }

	backgroundTexture.loadFromFile("resources/board.jpg");
	backgroundSprite.setTexture(backgroundTexture);

	whiteTexture.loadFromFile("resources/white.png");
	whiteSprite.setTexture(whiteTexture);
	whiteSprite.setOrigin(25, 25);

	blackTexture.loadFromFile("resources/black.png");
	blackSprite.setTexture(blackTexture);
	blackSprite.setOrigin(25, 25);

	whiteSpriteDecor = whiteSprite;
	whiteSpriteDecor.setPosition(25, 665);
	blackSpriteDecor = blackSprite;
	blackSpriteDecor.setPosition(575, 665);

	restartText.setFont(font);
	restartText.setPosition(300, 780);
	restartText.setString("(Press space to restart)");
	restartText.setCharacterSize(20);
	FloatRect rect = restartText.getLocalBounds();
	restartText.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
	restartText.setFillColor(Color::White);
	restartText.setOutlineColor(Color::Black);
	restartText.setOutlineThickness(1);

	displayText.setFont(font);
	displayText.setPosition(300, 720);
	displayText.setFillColor(Color::White);
	displayText.setOutlineColor(Color::Black);
	displayText.setOutlineThickness(1);

	whiteText.setFont(font);
	whiteText.setPosition(15, 600);
	whiteText.setFillColor(Color::White);
	whiteText.setOutlineColor(Color::Black);
	whiteText.setOutlineThickness(1);

	blackText.setFont(font);
	blackText.setPosition(570, 600);
	blackText.setFillColor(Color::Black);
	blackText.setOutlineColor(Color::Black);
	blackText.setOutlineThickness(1);

	markerSprite.setRadius(10);
	markerSprite.setOrigin(10, 10);
	markerSprite.setFillColor(Color::Green);
}

bool Graphics::isInCircle(sf::Vector2f position, const int& x, const int& y)
{
	if (sqrt((position.x - x) * (position.x - x) + (position.y - y) * (position.y - y)) < 25)
		return true;
	else
		return false;
}

void Graphics::drawMarkers(sf::RenderWindow& window)
{
	CircleShape markerTmp = markerSprite;
	for (auto item : markers)
	{
		int x = (int)getCoordinates(item).x;
		int y = (int)getCoordinates(item).y;
		markerTmp.setPosition((float)x, (float)y);
		window.draw(markerTmp);
	}
}

void Graphics::drawPieces(sf::RenderWindow& window)
{
	for (auto& item : boardPieces)
	{
		window.draw(item.second);
	}
}

int Graphics::getClickValue(Vector2f click)
{
	int value = -1;
	if (isInCircle(click, 25, 25))
		value = 0;
	else if (isInCircle(click, 300, 25))
		value = 1;
	else if (isInCircle(click, 575, 25))
		value = 2;
	else if (isInCircle(click, 110, 110))
		value = 3;
	else if (isInCircle(click, 300, 110))
		value = 4;
	else if (isInCircle(click, 490, 110))
		value = 5;
	else if (isInCircle(click, 190, 190))
		value = 6;
	else if (isInCircle(click, 300, 190))
		value = 7;
	else if (isInCircle(click, 405, 190))
		value = 8;
	else if (isInCircle(click, 25, 300))
		value = 9;
	else if (isInCircle(click, 110, 300))
		value = 10;
	else if (isInCircle(click, 190, 300))
		value = 11;
	else if (isInCircle(click, 405, 300))
		value = 12;
	else if (isInCircle(click, 490, 300))
		value = 13;
	else if (isInCircle(click, 575, 300))
		value = 14;
	else if (isInCircle(click, 190, 405))
		value = 15;
	else if (isInCircle(click, 300, 405))
		value = 16;
	else if (isInCircle(click, 405, 405))
		value = 17;
	else if (isInCircle(click, 110, 490))
		value = 18;
	else if (isInCircle(click, 300, 490))
		value = 19;
	else if (isInCircle(click, 490, 490))
		value = 20;
	else if (isInCircle(click, 25, 575))
		value = 21;
	else if (isInCircle(click, 300, 575))
		value = 22;
	else if (isInCircle(click, 575, 575))
		value = 23;
	return value;
}

Vector2f Graphics::getCoordinates(const int& n)
{
	Vector2f coord;
	switch (n)
	{
	case 0:
		coord = Vector2f(25, 25);
		break;
	case 1:
		coord = Vector2f(300, 25);
		break;
	case 2:
		coord = Vector2f(575, 25);
		break;
	case 3:
		coord = Vector2f(110, 110);
		break;
	case 4:
		coord = Vector2f(300, 110);
		break;
	case 5:
		coord = Vector2f(488, 110);
		break;
	case 6:
		coord = Vector2f(193, 191);
		break;
	case 7:
		coord = Vector2f(300, 191);
		break;
	case 8:
		coord = Vector2f(405, 191);
		break;
	case 9:
		coord = Vector2f(25, 300);
		break;
	case 10:
		coord = Vector2f(110, 300);
		break;
	case 11:
		coord = Vector2f(192, 300);
		break;
	case 12:
		coord = Vector2f(405, 300);
		break;
	case 13:
		coord = Vector2f(490, 300);
		break;
	case 14:
		coord = Vector2f(575, 300);
		break;
	case 15:
		coord = Vector2f(193, 405);
		break;
	case 16:
		coord = Vector2f(300, 405);
		break;
	case 17:
		coord = Vector2f(405, 405);
		break;
	case 18:
		coord = Vector2f(110, 488);
		break;
	case 19:
		coord = Vector2f(300, 488);
		break;
	case 20:
		coord = Vector2f(488, 488);
		break;
	case 21:
		coord = Vector2f(25, 573);
		break;
	case 22:
		coord = Vector2f(300, 573);
		break;
	case 23:
		coord = Vector2f(575, 575);
		break;
	}
	return coord;
}

void Graphics::resetGraphics()
{
	selectedToMove = -1;
	displayString = "Player 1: Place a piece!";
	whiteString = "9";
	blackString = "9";
	displayText.setFillColor(Color::White);
	markers.clear();
	markersVector.clear();
	boardPieces.clear();
}

void Graphics::drawGraphics(sf::RenderWindow& window)
{
	window.clear(Color::White);
	window.draw(backgroundSprite);
	drawPieces(window);
	setStrings();
	FloatRect rect = displayText.getLocalBounds();
	displayText.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
	window.draw(displayText);
	window.draw(whiteText);
	window.draw(blackText);
	window.draw(restartText);
	drawMarkers(window);
	window.draw(whiteSpriteDecor);
	window.draw(blackSpriteDecor);
	window.display();
}

void Graphics::setTextColor(const int& playerTurn)
{
	if (playerTurn)
		displayText.setFillColor(Color::White);
	else
		displayText.setFillColor(Color::Black);
}

void Graphics::setStrings()
{
	displayText.setString(displayString);
	whiteText.setString(whiteString);
	blackText.setString(blackString);
}
