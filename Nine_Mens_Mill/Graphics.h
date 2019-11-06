#pragma once

#include <SFML/Graphics.hpp>

class Graphics
{
private:
	bool isInCircle(sf::Vector2f position, const int& x, const int& y);
	void drawMarkers(sf::RenderWindow& window);
	void setStrings();

	sf::Text displayText;
	sf::Text whiteText;
	sf::Text blackText;
	sf::Text restartText;

	sf::Texture whiteTexture;
	sf::Texture blackTexture;
	sf::Texture backgroundTexture;

	sf::Sprite whiteSprite;
	sf::Sprite blackSprite;
	sf::Sprite backgroundSprite;
	sf::Sprite whiteSpriteDecor;
	sf::Sprite blackSpriteDecor;

	sf::Font font;

	sf::CircleShape markerSprite;

	std::vector<sf::CircleShape> markersVector;
public:
	int selectedToMove;
	std::string displayString;
	std::string whiteString;
	std::string blackString;

	std::vector<int> markers;
	std::map<int, sf::Sprite> boardPieces;

	Graphics();

	sf::Text getWhiteText() { return whiteText; }
	sf::Text getBlackText() { return blackText; }
	sf::Text getDisplayText() { return displayText; }
	sf::Sprite getWhiteSprite() { return whiteSprite; }
	sf::Sprite getBlackSprite() { return blackSprite; }
	sf::Sprite getBackgroundSprite() { return backgroundSprite; }

	void setTextColor(const int& playerTurn);

	void drawPieces(sf::RenderWindow& window);
	int getClickValue(sf::Vector2f click);
	sf::Vector2f getCoordinates(const int& n);

	void drawGraphics(sf::RenderWindow& window);

	void resetGraphics();
};

