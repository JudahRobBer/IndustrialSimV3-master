#pragma once
#include <SFML/Graphics.hpp>
#include "PopUp.h"
#include "AssetHandler.hpp"

class UpgradePopUp : public PopUp
{
public:
	UpgradePopUp(int, int, int, sf::Vector2f);
	~UpgradePopUp();

private:
	AssetHandler assetHandler;
};

