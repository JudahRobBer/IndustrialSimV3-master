#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "PopUpManager.h"
#include <iostream>


class Tile
{
public:

	Tile(int inp)
	{
		id = inp;
	}

	Tile(int inp, sf::Vector2f pos) : Tile(inp)
	{
		position = pos;
	}

	Tile()
	{

	}

	~Tile()
	{

	}


	int getId()
	{
		return id;
	}


	void setId(int inp)
	{
		id = inp;
	}

	
	void setTexture(sf::Texture* textptr)
	{
		textureRef = textptr;
	}

	sf::Texture* getTexture() const
	{
		return textureRef;
	}

	void setPosition(int x, int y)
	{
		position = sf::Vector2f(x, y);
	}

	sf::Vector2f& getPosition() 
	{
		return position;
	}

	virtual void update() //overwritten by developedTile
	{

	}

	void makePopup(sf::Vector2f mousePos, sf::RenderWindow& w, double zoom, sf::Vector2f offset, int mapSize, PopUpManager* manager)
	{
		// Half of the window - (# tiles / 2 * tile size * zoom) + (position * tile size * zoom)
		double xpos = w.getSize().x / 2.0 - mapSize * 50 * zoom + position.x * 100.0 * zoom + offset.x;
		double ypos = w.getSize().y / 2.0 - mapSize * 50 * zoom + position.y * 100.0 * zoom + offset.y;
		sf::FloatRect boundingBox(xpos, ypos, 100.0 * zoom, 100.0 * zoom);
		if (boundingBox.contains(mousePos))
		{
			//Add popup
			if(id >= 10) // dev
				manager->NewPopUp(mousePos.x, mousePos.y, id, position, 0);
			else if (id == - 1) //road
				manager->NewPopUp(mousePos.x, mousePos.y, id, position, 1);
			else if (id == -2) // warehouse
				manager->NewPopUp(mousePos.x, mousePos.y, id, position, 2);
			else
				manager->NewPopUp(mousePos.x, mousePos.y, id, position, -1);
		}
	}
	

	//ill leave it for now
	//but this shouldnt be necessary
	//as tile holds its own id
	void setBuildType(int buildType)
	{
		switch (buildType)
		{
			case -1:
				dev = false;
				road = false;
				warehouse = false;
				std::cout << "default set true";
				break;
			case 0: //Development
				dev = true;
				std::cout << "dev set true";
				break;
			case 1: //Road
				road = true;
				std::cout << "road set true";
				break;
			case 2: //Warehouse
				warehouse = true;
				std::cout << "warehouse set true";
				break;
		}
	}

protected:
	int id = 0;
	sf::Texture* textureRef = nullptr;
	sf::Vector2f position;
	bool dev = false, road = false, warehouse = false;
};