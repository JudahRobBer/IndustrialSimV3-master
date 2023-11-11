#include "ConstructionPopUp.h"

ConstructionPopUp::ConstructionPopUp(int xPos, int yPos, int id, sf::Vector2f cords)
{
	popUp.setPosition(sf::Vector2f(xPos, yPos));
	popUp.setSize(sf::Vector2f(300, 303));
	popUp.setTexture(&assetHandler.textures.get("popUp"));
	tileID = id;
	tileCords = cords;

	buttonBase.resize(3);
	buttonLabel.resize(3);

	buttonBase[0].setSize(sf::Vector2f(300, 90));
	buttonBase[0].setPosition(sf::Vector2f(xPos, yPos + 33));
	buttonBase[0].setFillColor(sf::Color::White);
	buttonBase[0].setOutlineColor(sf::Color::Black);
	buttonBase[0].setOutlineThickness(3);
	buttonLabel[0] = "    $250";
	button.push_back(new Button(buttonLabel[0], tileID + 10, assetHandler.fonts.get("basic"), buttonBase[0],
		&assetHandler.textures.get("ButtonSpriteSheet"), assetHandler.textRects["upgradeButton"]));

	buttonBase[1].setSize(sf::Vector2f(300, 90));
	buttonBase[1].setPosition(sf::Vector2f(xPos, yPos + 122));
	buttonBase[1].setFillColor(sf::Color::White);
	buttonBase[1].setOutlineColor(sf::Color::Black);
	buttonBase[1].setOutlineThickness(3);
	buttonLabel[1] = "    $100";
	button.push_back(new Button(buttonLabel[1], -1, assetHandler.fonts.get("basic"), buttonBase[1],
		&assetHandler.textures.get("ButtonSpriteSheet"), assetHandler.textRects["roadButton"]));
	//button[1]->setSpriteScale(2, 2);

	if (id != 0)
	{
		buttonBase[2].setSize(sf::Vector2f(300, 90));
		buttonBase[2].setPosition(sf::Vector2f(xPos, yPos + 211));
		buttonBase[2].setFillColor(sf::Color::White);
		buttonBase[2].setOutlineColor(sf::Color::Black);
		buttonBase[2].setOutlineThickness(3);
		buttonLabel[2] = "    $500";
		button.push_back(new Button(buttonLabel[2], -2, assetHandler.fonts.get("basic"), buttonBase[2],
			&assetHandler.textures.get("ButtonSpriteSheet"), assetHandler.textRects["wareHouseButton"]));
		button[2]->setSpriteScale(1.8, 1.8);
	}

}

ConstructionPopUp::~ConstructionPopUp()
{
	for (int i = 0; i < button.size(); i++)
	{
		delete button[i];
	}
}

