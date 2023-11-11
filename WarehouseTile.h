#pragma once
#include "DevelopedTile.h"
#include "ResourceTile.h"
#include <list>
#include <unordered_map>

class WarehouseTile : public DevelopedTile
{
public:
	WarehouseTile(int oldId) : undevelopedId(oldId)
	{
		setId(-2);
	}

	WarehouseTile(int oldId, sf::Vector2f pos)
	{
		setId(-2);
		position = pos;
	}
	~WarehouseTile()
	{

	}

	void empty();
	int getCurStorage();
	void addResources(int, int); //id, amount
	void addResourceTile(Tile*);
	std::vector<Tile*>& getResourceVect();
	int getUndevelopedId();
	bool decreaseResource(int, int); //returns whether operation was successfull
	bool increaseResource(int, int);

	std::unordered_map<int,int>& getStoredResources();

private:
	

	int totalCapacity = 100;
	int curTotal = 0;
	std::unordered_map<int, int> currResAmount;
	std::vector<Tile*> connectedRes;
	int undevelopedId;
	
};

