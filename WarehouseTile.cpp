#include "WarehouseTile.h"


void WarehouseTile::empty()
{
	curTotal = 0;
	for (auto& x : currResAmount)
		x.second = 0;
}

int WarehouseTile::getCurStorage()
{
	int sum = 0;
	for (auto& x : currResAmount)
		sum += x.second;

	return sum;
}

void WarehouseTile::addResources(int id, int amount)
{
	if (getCurStorage() < totalCapacity)
		currResAmount[id] += amount;
}

void WarehouseTile::addResourceTile(Tile* tileptr)
{
	connectedRes.push_back(tileptr);
}


std::unordered_map<int, int>& WarehouseTile::getStoredResources()
{
	return currResAmount;
}

std::vector<Tile*>& WarehouseTile::getResourceVect()
{
	return connectedRes;
}

int WarehouseTile::getUndevelopedId()
{
	return undevelopedId;
}

bool WarehouseTile::decreaseResource(int id, int amount)
{
	if (currResAmount[id] - amount >= 0)
	{
		currResAmount[id] -= amount;
		return true;
	}
	return false;
}


bool WarehouseTile::increaseResource(int id, int amount)
{
	if (currResAmount[id] += amount <= totalCapacity)
	{
		currResAmount[id] += amount;
		return true;
	}
	return false;
}