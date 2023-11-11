#pragma once
#include <SFML/Graphics.hpp>
#include "PopUp.h"
#include "AssetHandler.hpp"

class ConstructionPopUp : public PopUp
{
public:
	ConstructionPopUp(int, int, int, sf::Vector2f);
	~ConstructionPopUp();

private:
	AssetHandler assetHandler;
};