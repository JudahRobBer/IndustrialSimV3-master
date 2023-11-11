#pragma once
#include <vector>
#include "StockpilePopUp.h"
#include "ConstructionPopUp.h"
#include "UpgradePopUp.h"

class PopUpManager
{
public:
	PopUpManager();
	~PopUpManager();

	void UpdatePopUps(sf::RenderWindow&);

	void NewPopUp(int, int, int, sf::Vector2f, int);
	void RemovePopUp();
	int PopUpHoldCheck(int, int);
	void MoveHeldPopUp(int, int);
	int ButtonPressed(int, int);
	int getPopUpNum();
	sf::Vector2f getTilePos();
private:
	std::vector<PopUp*> CurrentPopUp;
	int heldPopUp;
};

