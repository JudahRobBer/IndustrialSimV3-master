#pragma once
#include "Tile.hpp"
class LandTile : public Tile
{
public:

	LandTile(int inp) : Tile(inp)
	{

	}

	LandTile(int inp, sf::Vector2f pos) : Tile(inp, pos)
	{

	}
	
	~LandTile()
	{

	}



private:
	
};

