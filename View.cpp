#include "View.h"

void View::setOffset(double offx, double offy)
{
	offsetPos.x = offx;
	offsetPos.y = offy;
}

void View::changeOffset(double offx, double offy, int mapSize)
{
	offsetAcc.x = offx / zoom;
	offsetAcc.y = offy / zoom;

	offsetVel.x += offsetAcc.x;
	offsetVel.y += offsetAcc.y;

	offsetPos.x += offsetVel.x;
	offsetPos.y += offsetVel.y;

	offsetVel.x *= 0.5;
	offsetVel.y *= 0.5;

	if (offsetPos.x < -mapSize * 40 * zoom)
	{
		offsetPos.x = -mapSize * 40 * zoom;
	}
	if (offsetPos.x > mapSize * 40 * zoom)
	{
		offsetPos.x = mapSize * 40 * zoom;
	}
	if (offsetPos.y < -mapSize * 40 * zoom)
	{
		offsetPos.y = -mapSize * 40 * zoom;
	}
	if (offsetPos.y > mapSize * 40 * zoom)
	{
		offsetPos.y = mapSize * 40 * zoom;
	}
}

sf::Vector2f View::getOffset()
{
	return offsetPos;
}

void View::setZoom(double zoomSet)
{
	zoom = zoomSet;
}

void View::changeZoom(double zoomDiff)
{
	zoomacc = zoomDiff * zoom * 2;
	zoomvel += zoomacc;
	zoom += zoomvel * 0.05;
	if (zoom < 0.05)
		zoom = 0.05;
	if (zoom > 5)
		zoom = 5;
	zoomvel *= 0.5;
}

double View::getZoom()
{
	return zoom;
}
