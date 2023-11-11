#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "AssetHandler.hpp"
#include "Market.h"

class MarketPopUp
{
public:
	MarketPopUp(int, int, Market);
	~MarketPopUp();

	void draw(sf::RenderWindow&);
	int buttonPressed(int, int);
	bool closeCheck(int, int);
	void priceUpdate(Market);

private:
	AssetHandler assetHandler;
	std::string resources[4] = { "Coal", "Wood", "Iron", "Fish" };

	std::vector<sf::RectangleShape> buttonBase;
	std::vector<std::string> buttonLabel;
	std::vector<sf::Text> rates;
	std::vector<int> prices;
	std::vector<Button*> button;

	sf::RectangleShape marketBase;
};