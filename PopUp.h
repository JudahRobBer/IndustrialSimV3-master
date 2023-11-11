#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
class PopUp
{
public:
	PopUp();
	~PopUp();

	void displayWindow(sf::RenderWindow&);
	void displayButtons(sf::RenderWindow&);
	void createPopUp(int, int);
	void moveWindow(int, int);
	int windowCollision(int, int);
	int buttonUpdate(int, int);
	int getID();
	sf::Vector2f getTileCords();

protected:
	std::vector<sf::RectangleShape> buttonBase;
	std::vector<std::string> buttonLabel;
	std::vector<Button*> button;

	sf::RectangleShape popUp;
	sf::Vector2f tileCords;
	int dragOffsetX = 0;
	int dragOffsetY = 0;
	int tileID;
};

