#pragma once
#include "Tile.hpp"
class DevelopedTile : public Tile
{
public:
	DevelopedTile(int inp) : Tile(inp)
	{

	}

	DevelopedTile(int inp, sf::Vector2f pos) : Tile(inp, pos)
	{

	}

	DevelopedTile()
	{

	}
	
	~DevelopedTile()
	{

	}


	virtual void update() //increment resource amount
	{

	}
};

