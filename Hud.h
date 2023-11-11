#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "Button.h"
#include "AssetHandler.hpp"
class Hud
{
public:
	Hud();
	~Hud();

	//texture held at 0 is iteam bar, 1 is for timeWindow
	void assignTextures(const std::vector<sf::Texture*>&);
	
	//initialized once at start
	void setFont(sf::Font*);
	void setButtons();

	//pull values held in game into texts to be displayed
	void updateAssetValues(const std::vector<int>&);
	void updateTime();

	//takes window size to rescale hud horizontally
	void updateHudPosition(int);

	//Updates time based on buttons pressed
	void buttonUpdate(sf::Vector2f);

	//for use by animator
	sf::RectangleShape* getItemBar();
	std::vector<sf::Sprite*> getItems();
	std::vector<sf::Text*> getTexts();
	std::vector<Button*> getButton();
	int* getCalander();
	int getGameSpeed();
	bool getMonthTick();


private:
	sf::RectangleShape itemBar;
	std::vector<sf::Sprite> items;

	//HUD DOES NOT MAINTAIN FONT LIFETIME
	sf::Font* fontptr = nullptr;

	//holds text object and assocaited value: 0 (money), 1 (coal), 2 (wood), 3 (steel), 4 (time)
	std::vector<std::pair<sf::Text,int>> texts;
	
	std::vector<sf::RectangleShape> buttonBase;
	std::string buttonText = " ";
	std::vector<std::string> buttonName = { "pause", "1speed", "3speed", "10speed" };
	int speedValues[4] = { 0,1,3,10 };
	int calander[3] = { 1,1,1900 };
	bool monthTick = false;
	std::vector<Button*> button;

	int currentSpeed = 0;

	AssetHandler assetHandler;
};

