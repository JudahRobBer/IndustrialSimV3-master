#include "ResourceTile.h"


void ResourceTile::update()
{
	if (storage < capacity)
		storage += generatedPerTurn;
	std::cout <<"updated " << storage << std::endl;
}


//establish connection between resource tile and warehouse after check if connected in tile map
void ResourceTile::connectToWarehouse(Tile* ptr)
{
	wareHouseptr = ptr;
	connected = true;
}

//tranfsers stored goods to connected warehouse
void ResourceTile::empty()
{
	WarehouseTile* temp = (WarehouseTile*)wareHouseptr;

	if (temp != nullptr)
		temp->addResources(getId(), storage);
		
	storage = 0;
	std::cout << "emptied " << storage << std::endl;
}

int ResourceTile::getCurStorage()
{
	return storage;
}

bool ResourceTile::isConnected()
{
	return connected;
}

void ResourceTile::disconnect()
{
	wareHouseptr = nullptr;
	connected = false;
}

Tile* ResourceTile::getWarehousePtr()
{
	return wareHouseptr;
}

void ResourceTile::upgrade()
{
	generatedPerTurn++;
}

bool ResourceTile::canUpgrade()
{
	if (level < maxLevel)
		return true;
	return false;
}
