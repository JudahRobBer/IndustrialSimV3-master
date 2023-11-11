#include "PopUp.h"


PopUp::PopUp()
{
}

PopUp::~PopUp()
{

}


void PopUp::displayWindow(sf::RenderWindow& w)
{
	w.draw(popUp);
	displayButtons(w);
}

void PopUp::displayButtons(sf::RenderWindow& w)
{
	for (Button* x : button)
	{
		w.draw(*x);
	}
}

void PopUp::createPopUp(int xsize, int ysize)
{
	popUp.setSize(sf::Vector2f(xsize, ysize));
}

void PopUp::moveWindow(int xVel, int yVel)
{
	popUp.setPosition(xVel - dragOffsetX, yVel - dragOffsetY);
	for (int i = 0; i < button.size(); i++)
	{
		button[i]->setPosition(xVel - dragOffsetX, yVel - dragOffsetY + (89*i) +33);
	}
}

int PopUp::windowCollision(int x, int y)
{
	if (popUp.getGlobalBounds().contains(x, y))
	{
		dragOffsetX = x - popUp.getPosition().x;
		dragOffsetY = y - popUp.getPosition().y;

		if (dragOffsetY < 30) // titlebar like space 300x30
		{
			if (popUp.getSize().x - dragOffsetX < 30) // top right corner 30x30
				return 2; // Close
			return 1; // Move
		}
		return 3; // other interactions
	}
	return 0; // not held
}

int PopUp::buttonUpdate(int x, int y)
{
	int temp = tileID;
	for (int i = 0; i < button.size(); i++)
	{
		sf::FloatRect bounds = button[i]->getBounds();
		if (bounds.contains(sf::Vector2f(x, y)))
		{
			tileID = button[i]->getValue();
		}
	}
	if (temp != tileID) // dont return id if no change
		return tileID;
	else
		return -10;
}

int PopUp::getID()
{
	return tileID;
}

sf::Vector2f PopUp::getTileCords()
{
	return tileCords;
}
