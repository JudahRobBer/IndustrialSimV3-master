#pragma once
#include "Engine.h"
#include <iostream>

class View
{
public:
	void setOffset(double, double);
	void changeOffset(double, double, int);
	sf::Vector2f getOffset();

	void setZoom(double);
	void changeZoom(double);
	double getZoom();

private:

	sf::Vector2f offsetPos;
	sf::Vector2f offsetVel;
	sf::Vector2f offsetAcc;
	double zoomacc = 0, zoomvel = 0, zoom = 1;
};

