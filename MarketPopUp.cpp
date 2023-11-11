#include "MarketPopUp.h"

MarketPopUp::MarketPopUp(int xPos, int yPos, Market market)
{
	std::cout << "MARKET MADE\n";

	marketBase.setPosition(sf::Vector2f(xPos, yPos));
	marketBase.setSize(sf::Vector2f(800, 390));
	marketBase.setTexture(&assetHandler.textures.get("popUpLong"));

	buttonBase.resize(24);
	buttonLabel.resize(24);
	rates.resize(8);

	prices = market.getPrices();

	int buttonNum = 0;

	for (int a = 0; a < 2; a++)
	{
		for (int i = 0; i < 4; i++)
		{
			buttonBase[i * 2].setSize(sf::Vector2f(100, 84));
			buttonBase[i * 2].setPosition(sf::Vector2f(xPos + (400 * a), yPos + (i * 90) + 33));
			if(a == 1)
				buttonBase[i * 2].setFillColor(sf::Color(100,255,100));
			else
				buttonBase[i * 2].setFillColor(sf::Color(255, 100, 100));
			buttonBase[i * 2].setOutlineColor(sf::Color::Black);
			buttonBase[i * 2].setOutlineThickness(3);
			button.push_back(new Button("1", buttonNum, assetHandler.fonts.get("basic"), buttonBase[i * 2],
				&assetHandler.textures.get("HUD_" + resources[i]), sf::IntRect(0, 0, 200, 200)));
			buttonNum++;

			buttonBase[i * 2 + 1].setSize(sf::Vector2f(100, 84));
			buttonBase[i * 2 + 1].setPosition(sf::Vector2f(xPos + 100 + (400 * a), yPos + (i * 90) + 33));
			if (a == 1)
				buttonBase[i * 2+1].setFillColor(sf::Color(100, 255, 100));
			else
				buttonBase[i * 2+1].setFillColor(sf::Color(255, 100, 100));
			buttonBase[i * 2 + 1].setOutlineColor(sf::Color::Black);
			buttonBase[i * 2 + 1].setOutlineThickness(3);
			button.push_back(new Button("5", buttonNum, assetHandler.fonts.get("basic"), buttonBase[i * 2 + 1],
				&assetHandler.textures.get("HUD_" + resources[i]), sf::IntRect(0, 0, 200, 200)));
			buttonNum++;

			buttonBase[i * 2 + 2].setSize(sf::Vector2f(100, 84));
			buttonBase[i * 2 + 2].setPosition(sf::Vector2f(xPos + 200 + (400 * a), yPos + (i * 90) + 33));
			if (a == 1)
				buttonBase[i * 2+2].setFillColor(sf::Color(100, 255, 100));
			else
				buttonBase[i * 2+2].setFillColor(sf::Color(255, 100, 100));
			buttonBase[i * 2 + 2].setOutlineColor(sf::Color::Black);
			buttonBase[i * 2 + 2].setOutlineThickness(3);
			button.push_back(new Button("50", buttonNum, assetHandler.fonts.get("basic"), buttonBase[i * 2 + 2],
				&assetHandler.textures.get("HUD_" + resources[i]), sf::IntRect(0, 0, 200, 200)));
			buttonNum++;
		}
	}

	for (int a = 0; a < 4; a++)
	{
		rates[a * 2].setString(std::to_string(prices[a * 2]));
		rates[a * 2].setFont(assetHandler.fonts.get("basic"));
		rates[a * 2].setCharacterSize(48);
		rates[a * 2].setFillColor(sf::Color::Black);
		rates[a * 2].setPosition(sf::Vector2f(xPos + 325, yPos + 33 + (a * 90)));

		rates[a * 2 + 1].setString(std::to_string(prices[a * 2 + 1]));
		rates[a * 2 + 1].setFont(assetHandler.fonts.get("basic"));
		rates[a * 2 + 1].setCharacterSize(48);
		rates[a * 2 + 1].setFillColor(sf::Color::Black);
		rates[a * 2 + 1].setPosition(sf::Vector2f(xPos + 725, yPos + 33 + (a * 90)));
	}
}

MarketPopUp::~MarketPopUp()
{
	for (int i = 0; i < button.size(); i++)
	{
		delete button[i];
	}
}

void MarketPopUp::draw(sf::RenderWindow& w)
{
	w.draw(marketBase);

	for (int i = 0; i < button.size(); i++)
	{
		w.draw(*button[i]);
	}

	for (int i = 0; i < rates.size(); i++)
	{
		w.draw(rates[i]);
	}
}

int MarketPopUp::buttonPressed(int x, int y)
{
	for (int i = 0; i < button.size(); i++)
	{
		sf::FloatRect bounds = button[i]->getBounds();
		if (bounds.contains(sf::Vector2f(x, y)))
		{
			return button[i]->getValue();
		}
	}
	return -1;
}

bool MarketPopUp::closeCheck(int x, int y)
{
	if (marketBase.getGlobalBounds().contains(x, y))
	{
		int dragOffsetX = x - marketBase.getPosition().x;
		int dragOffsetY = y - marketBase.getPosition().y;

		if (dragOffsetY < 30) // titlebar like space 300x30
		{
			if (marketBase.getSize().x - dragOffsetX < 30) // top right corner 30x30
				return true; // Close
		}
	}
	return false;
}

void MarketPopUp::priceUpdate(Market market)
{
	prices = market.getPrices();

	for (int a = 0; a < 4; a++)
	{
		rates[a * 2].setString(std::to_string(prices[a * 2]));

		rates[a * 2 + 1].setString(std::to_string(prices[a * 2 + 1]));
	}
}
