#include "UpgradePopUp.h"

UpgradePopUp::UpgradePopUp(int xPos, int yPos, int id, sf::Vector2f cords)
{
	popUp.setPosition(sf::Vector2f(xPos, yPos));
	popUp.setSize(sf::Vector2f(300, 202));
	popUp.setTexture(&assetHandler.textures.get("popUpShort"));
	tileID = id;
	tileCords = cords;

	buttonBase.resize(2);
	buttonLabel.resize(2);

	if (id < 99 && id > -1)
	{
	buttonBase[0].setSize(sf::Vector2f(300, 90));
	buttonBase[0].setPosition(sf::Vector2f(xPos, yPos + 33));
	buttonBase[0].setFillColor(sf::Color::White);
	buttonBase[0].setOutlineColor(sf::Color::Black);
	buttonBase[0].setOutlineThickness(3);
	buttonLabel[0] = "    " + std::to_string(250 + (id/10) *250); // increace price with each upgrade
	button.push_back(new Button(buttonLabel[0], tileID + 10, assetHandler.fonts.get("basic"), buttonBase[0],
		&assetHandler.textures.get("ButtonSpriteSheet"), assetHandler.textRects["upgradeButton"]));
	}
	else // Maxed out Location
	{
		buttonBase[0].setSize(sf::Vector2f(300, 90));
		buttonBase[0].setPosition(sf::Vector2f(xPos, yPos + 33));
		buttonBase[0].setFillColor(sf::Color::White);
		buttonBase[0].setOutlineColor(sf::Color::Black);
		buttonBase[0].setOutlineThickness(3);
		buttonLabel[0] = "    MAX";
		button.push_back(new Button(buttonLabel[0], tileID, assetHandler.fonts.get("basic"), buttonBase[0],
			&assetHandler.textures.get("ButtonSpriteSheet"), assetHandler.textRects["upgradeButton"]));
	}
	buttonBase[1].setSize(sf::Vector2f(300, 90));
	buttonBase[1].setPosition(sf::Vector2f(xPos, yPos + 122));
	buttonBase[1].setFillColor(sf::Color::White);
	buttonBase[1].setOutlineColor(sf::Color::Black);
	buttonBase[1].setOutlineThickness(3);
	buttonLabel[1] = "    DESTROY"; // increace price with each upgrade
	button.push_back(new Button(buttonLabel[1], tileID % 10, assetHandler.fonts.get("basic"), buttonBase[1],
		&assetHandler.textures.get("ButtonSpriteSheet"), assetHandler.textRects["upgradeButton"]));
}

UpgradePopUp::~UpgradePopUp()
{
	for (int i = 0; i < button.size(); i++)
	{
		delete button[i];
	}
}

