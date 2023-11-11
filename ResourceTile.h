#pragma once
#include "DevelopedTile.h"
#include "WarehouseTile.h"

class ResourceTile : public DevelopedTile
{
public:
	ResourceTile(int inp) : DevelopedTile(inp)
	{

	}

	ResourceTile(int inp, sf::Vector2f pos) : DevelopedTile(inp, pos)
	{

	}

	~ResourceTile()
	{

	}

	void update();
	void upgrade();
	bool canUpgrade();
	void connectToWarehouse(Tile*);
	void empty();
	int getCurStorage();
	bool isConnected();
	void disconnect();
	Tile* getWarehousePtr();



private:
	
	
	int capacity = 20;
	int storage = 0;
	int generatedPerTurn = 1;
	int level = 1;
	int maxLevel = 10;
	bool full = false;
	bool connected = false;
	Tile* wareHouseptr;

};

