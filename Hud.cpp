#include "Hud.h"
#include <string>
#include <iostream>


Hud::Hud()
{
	//to be adjusted?
	texts.resize(6);
	setButtons();
}

Hud::~Hud()
{

}

void Hud::assignTextures(const std::vector<sf::Texture*>& textures)
{
	itemBar.setSize(sf::Vector2f(1000, 100));
	itemBar.setFillColor(sf::Color(135, 135, 135));
	//timeWindow.setTextureRect(sf::IntRect(0, 0, 87, 82));
	for (int i = 0; i < textures.size(); i++)
	{
		items.push_back(sf::Sprite(*textures[i]));
		items[i].setPosition(200 * i, 10);
		items[i].setScale(.4, .4);
	}
}


//setFont also initializes the text, this functions serves as initializer
void Hud::setFont(sf::Font* ft)
{
	fontptr = ft;
	int offset = 80;
	int dOffset = 200;
	for (auto& itr : texts)
	{
		itr.first.setFont(*fontptr);
		itr.second = 0;
		itr.first.setString(std::to_string(itr.second));
		itr.first.setPosition(sf::Vector2f(offset, 30));
		offset += dOffset;
	}
}

void Hud::setButtons()
{
	buttonBase.resize(4);

	for (int i = 0; i < buttonBase.size(); i++)
	{
		buttonBase[i].setSize(sf::Vector2f(37, 40));
		buttonBase[i].setPosition(sf::Vector2f(800 + (50 * i), 60));
		buttonBase[i].setFillColor(sf::Color::White);
		buttonBase[i].setOutlineColor(sf::Color::Black);
		buttonBase[i].setOutlineThickness(3);

		button.push_back(new Button(buttonText, speedValues[i], assetHandler.fonts.get("basic"), buttonBase[i],
		&assetHandler.textures.get("timeButtons"), assetHandler.textRects[buttonName[i]]));

		button[i]->setSpriteScale(1.8, 1.8);
	}


	button[0]->setColor(sf::Color(100, 100, 100));
}

void Hud::updateAssetValues(const std::vector<int>& vals)
{
	for (int i = 0; i < vals.size(); i++)
	{
		texts[i].second = vals[i];
		texts[i].first.setString(std::to_string(texts[i].second));
	}
}

void Hud::updateTime()
{
	if (calander[1] == 2 && calander[0] == 28 && calander[2] % 4 == 0) // Leap Year
	{
		calander[0] = 1;
		calander[1]++;
		monthTick = true;
	}
	else if (calander[1] == 2 && calander[0] == 28) // Normal Feb
	{
		calander[0] = 1;
		calander[1]++;
		monthTick = true;
	}
	else if ((calander[1] == 4 || calander[1] == 6 || calander[1] == 9 || calander[1] == 11) && calander[0] == 30) // 30 doy month
	{
		calander[0] = 1;
		calander[1]++;
		monthTick = true;
	}
	else if (calander[0] == 31) // 31 doy month
	{
		calander[0] = 1;
		calander[1]++;
		monthTick = true;
	}
	else // Normal day
	{
		calander[0]++;
	}

	if (calander[1] == 13) // year increment
	{
		calander[1] = 1;
		calander[2]++;
	}

	texts[texts.size() - 1].first.setOrigin(texts[texts.size() - 1].first.getLocalBounds().width / 2, 0);
	texts[texts.size() - 1].first.setString(std::to_string(calander[1]) + "/" + std::to_string(calander[0]) + "/" + std::to_string(calander[2]));
	return;
}

int* Hud::getCalander()
{
	return calander;
}

void Hud::updateHudPosition(int hudLength)
{
	itemBar.setSize(sf::Vector2f(hudLength, 100));

	for (int i = 0; i < items.size(); i++)
		items[i].setPosition((hudLength/6) * i, 10);

	for (int i = 0; i < texts.size()-1; i++)
		texts[i].first.setPosition(sf::Vector2f((hudLength*.08)+(hudLength / 6) * i, 30));
	texts[texts.size() - 1].first.setOrigin(texts[texts.size() - 1].first.getLocalBounds().width / 2, 0);
	texts[texts.size() - 1].first.setPosition(sf::Vector2f((hudLength * .08) + (hudLength / 10) * 8, 10));
	texts[texts.size() - 1].first.setString(std::to_string(calander[1]) + "/" + std::to_string(calander[0]) + "/" + std::to_string(calander[2]));

	for (int i = 0; i < button.size(); i++)
		button[i]->setPosition((hudLength*.8) + ((hudLength*.05)*i), 60);
}

void Hud::buttonUpdate(sf::Vector2f mousePos)
{
	for (int i = 0; i < button.size(); i++)
	{
		sf::FloatRect bounds = button[i]->getBounds();
		if (bounds.contains(sf::Vector2f(mousePos.x, mousePos.y)))
		{
			currentSpeed = button[i]->getValue();
			for (int a = 0; a < button.size(); a++)
				button[a]->setColor(sf::Color::White);
			button[i]->setColor(sf::Color(100, 100, 100));
		}
	}
}

sf::RectangleShape* Hud::getItemBar()
{
	return &itemBar;
}

std::vector<sf::Sprite*> Hud::getItems()
{
	{
		std::vector<sf::Sprite*> itemsVect;
		for (auto& itr : items)
		{
			itemsVect.push_back(&itr);
		}
		return itemsVect;
	}
}

std::vector<sf::Text*> Hud::getTexts()
{
	std::vector<sf::Text*> textVect;
	for (auto& itr : texts)
	{
		textVect.push_back(&itr.first);
	}
	return textVect;
}

std::vector<Button*> Hud::getButton()
{
	std::vector<Button*> buttonVect;
	for (auto& itr : button)
	{
		buttonVect.push_back(itr);
	}
	return buttonVect;
}

int Hud::getGameSpeed()
{
	return currentSpeed;
}

bool Hud::getMonthTick() // retruns if to add resources for end of month
{
	if (monthTick)
	{
		monthTick = false;
		return true;
	}
	return false;

}

