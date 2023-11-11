#include "TileMap.h"
#include "PerlinGenerator.h"
#include <random>
#include <stack>
#include <queue>
#include <iostream>


TileMap::TileMap()
{
	//initialize 32x32 map
	map.resize(MAPSIZE);
	for (auto& x : map)
		x.resize(MAPSIZE);

	
	initTerrain();

	vertTerrain.setPrimitiveType(sf::Quads);
	vertTerrain.resize(MAPSIZE * MAPSIZE * 4);

	updateTextures();

}

TileMap::~TileMap()
{
	for (auto& x : map)
		for (auto& y : x)
			delete y;
}


void TileMap::initTerrain()
{
	int yitr = 0;
	int xitr = 0;
	

	
	//initialize base terrain
	for (auto& x : map)
	{
		for (auto& y : x)
		{
			y = new LandTile(2);
			y->setPosition(xitr,yitr);
			xitr++;
		}
		xitr = 0;
		yitr++;
	}

	PerlinGenerator perlinGenerator(MAPSIZE, MAPSIZE);
	perlinGenerator.SetNoiseOctaves(2);
	perlinGenerator.SetAmplitude(1);
	perlinGenerator.SetNoisePersistence(1);

	float** percocete = perlinGenerator.GenerateMap();


	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			if (percocete[i][j] <= .33)
				map[i][j]->setId(0);
			else if (percocete[i][j] <= .45)
				map[i][j]->setId(1);
			else if (percocete[i][j] <= .66)
				map[i][j]->setId(2);
			else
				map[i][j]->setId(3);

		}
	}
}




std::vector<std::vector<Tile*>>& TileMap::getMap()
{
	return map;
}



bool TileMap::isValid(bool visited[32][32], int row, int col)
{
	
	if (row < 0 || col < 0 || row >= MAPSIZE || col >= MAPSIZE)
		return false;


	if (visited[col][row])
	{
		std::cout << row << " " << col << " is already visited" << std::endl;
		return false;
	}

	if (map[col][row]->getId() == -1 || map[col][row]->getId() == -2)
	{
		std::cout << row << " " << col << " " << "is valid" << std::endl;
		return true;
	}

	return false;
}

//breadth first search run to determine if path (roads) connects two tiles, typically Warehouse and Resource Tiles
//shortest path is not considered as length of road currently has no impact
//depth first search tends to explore in an inefficient manner given that tiles tend to be more densly packed with more connecting roads
bool TileMap::canConnect(Tile* s, Tile* d)
{
	//visited set
	bool visited[32][32];
	memset(visited, false, sizeof visited);
	
	//bfs queue
	std::queue<std::pair<int, int>> queue;

	//used for accessing adjacent tiles
	int dRow[] = { 0, 1, 0, -1 };
	int dCol[] = { -1, 0, 1, 0 };

	//std::pair acts as a convenient way to store coordinates
	std::pair<int, int> destCoords(d->getPosition().x, d->getPosition().y);
	sf::Vector2i vect = (sf::Vector2i)s->getPosition();
	
	visited[vect.x][vect.y] = true;
	queue.push(std::pair<int, int>(s->getPosition().x, s->getPosition().y));

	while (!queue.empty())
	{
		//visit front of queue, remove from queue, check if destination is reached
		std::pair<int, int> temp = queue.front();
		std::cout << "Exploring " << temp.first << " " << temp.second << std::endl;
		queue.pop();
		
		if (temp == destCoords)
			return true;
		
		
		int row = temp.first;
		int col = temp.second;


		visited[row][col] = true;
		
		

		//if not, explore all neighbors looking for valid roads
		for (int i = 0; i < 4; i++) 
		{
			int adjx = row + dRow[i];
			int adjy = col + dCol[i];
			if (isValid(visited, adjx, adjy))
				queue.push({ adjx, adjy });
			else
				std::cout << adjx << " " << adjy << " is not valid" << std::endl;
		}
	}
	return false;
}

void TileMap::clickCheck(sf::Vector2f mousePos, sf::RenderWindow &w, double zoom, sf::Vector2f offset, int mapSize, PopUpManager* manager)
{
	for (auto& tileVect : map)
	{
		for (auto& tile : tileVect)
		{
			tile->makePopup(mousePos, w, zoom, offset, mapSize, manager);
		}
	}
}

//set the development type of a tile, 0 is dev, 1 is road, 2 is warehouse
void TileMap::setDevelopmentType(int row, int col, int buildType, int id)
{
	map[row][col]->setBuildType(buildType);
	map[row][col]->setId(id);
}

int TileMap::getMapSize()
{
	return MAPSIZE;
}

sf::VertexArray& TileMap::getVertexTerrain()
{
	return vertTerrain;
}


void TileMap::updateTextures()
{
	std::unordered_map<int, sf::Vector2f> texMap;
	int neigh[4];
	int average = 0;

	texMap[HILLS] = sf::Vector2f(192, 0);
	texMap[PLAINS] = sf::Vector2f(64, 0);
	texMap[FOREST] = sf::Vector2f(128, 0);
	texMap[WATER] = sf::Vector2f(0, 0);

	for (int x = 0; x < MAPSIZE; x++)
		for (int y = 0; y < MAPSIZE; y++)
		{
			vertTerrain[(x + y * MAPSIZE) * 4 + 0].texCoords = sf::Vector2f(texMap[map[x][y]->getId()].x + 0, texMap[map[x][y]->getId()].y + 0);
			vertTerrain[(x + y * MAPSIZE) * 4 + 1].texCoords = sf::Vector2f(texMap[map[x][y]->getId()].x + 64, texMap[map[x][y]->getId()].y + 0);
			vertTerrain[(x + y * MAPSIZE) * 4 + 2].texCoords = sf::Vector2f(texMap[map[x][y]->getId()].x + 64, texMap[map[x][y]->getId()].y + 64);
			vertTerrain[(x + y * MAPSIZE) * 4 + 3].texCoords = sf::Vector2f(texMap[map[x][y]->getId()].x + 0, texMap[map[x][y]->getId()].y + 64);
		}
}

void TileMap::developTile(int row, int col, int id)
{	
	Tile* temp = map[row][col];
	map[row][col] = new ResourceTile(temp->getId() + 10);
	map[row][col]->setPosition(temp->getPosition().x, temp->getPosition().y);
	setTileTexture(row, col, map[row][col]->getId());

	std::cout << "tile developed at " << col << " " << row << std::endl;
	std::cout << "Id is " << map[row][col]->getId() << std::endl;

	bool connected = false;
	for (WarehouseTile* warehouse : warehouseTiles)
	{
		if (!connected && canConnect(map[row][col], warehouse))
		{
			ResourceTile* resourceDownCast = (ResourceTile*)map[row][col];
			resourceDownCast->connectToWarehouse(warehouse);
			warehouse->addResourceTile(map[row][col]);
			std::cout << "Developed tile was connected to a warehouse!" << std::endl;
			connected = true;
		}
	}

	if (connected)
	{
		resourceTiles.push_back((ResourceTile*)map[row][col]);
	}
	else
	{
		std::cout << "unconnected tile" << std::endl;
		unconnectedResourceTiles.push_back((ResourceTile*)map[row][col]);
	}

	delete temp;
}

void TileMap::buildWareHouse(int row, int col, int id)
{
	 
	Tile* temp = map[row][col];
	map[row][col] = new WarehouseTile(temp->getId());
	map[row][col]->setPosition(temp->getPosition().x, temp->getPosition().y);
	warehouseTiles.push_back((WarehouseTile*)map[row][col]);
	attemptNewWarehouseConnection((WarehouseTile*)map[row][col]);
	setTileTexture(row, col, WAREHOUSE);
	delete temp;

	std::cout << "Warehouse Created at " << col << " " << row << std::endl;
	std::cout << "Id is " << map[row][col]->getId() << std::endl;
}

void TileMap::buildRoad(int row, int col, int id)
{
	

	Tile* temp = map[row][col];
	//this allows for roads to be undeveloped
	map[row][col] = new RoadTile(temp->getId(),temp->getPosition());
	map[row][col]->setPosition(temp->getPosition().x, temp->getPosition().y);
	setTileTexture(row, col, ROAD);
	delete temp;
	
	std::cout << "Road Created at " << col << " " << row << std::endl;
	std::cout << "Id is " << map[row][col]->getId() << std::endl;

	for (auto warehouse : warehouseTiles)
		attemptNewWarehouseConnection(warehouse);

}

void TileMap::upgradeTile(int row, int col)
{
	ResourceTile* downcast = (ResourceTile*)map[row][col];
	if (downcast->canUpgrade())
		downcast->upgrade();
}

void TileMap::updateResourceTiles()
{
	for (ResourceTile* tile : resourceTiles)
	{
		tile->update();
		tile->empty();
		//always tries to empty resources into connected warehouse
		//even if warehouse is full, resouces will be depleted
		//bug or feature? <--- that one
		
	}
	for (ResourceTile* tile : unconnectedResourceTiles)
	{
		tile->update();
	}
}


void TileMap::setTileTexture(int row, int col, int build)
{
	//std::cout << "row: " << row << " col: " << col << " index: " << row * col * MAPSIZE << '\n';
	std::unordered_map<int, sf::Vector2f> texMap;

	texMap[FISH] = sf::Vector2f(576, 0);
	texMap[LUMBER] = sf::Vector2f(256, 0);
	texMap[COAL] = sf::Vector2f(320, 0);
	texMap[IRON] = sf::Vector2f(384, 0);
	texMap[WAREHOUSE] = sf::Vector2f(512, 0);
	texMap[ROAD] = sf::Vector2f(448, 0);

	texMap[HILLS] = sf::Vector2f(192, 0);
	texMap[PLAINS] = sf::Vector2f(64, 0);
	texMap[FOREST] = sf::Vector2f(128, 0);
	texMap[WATER] = sf::Vector2f(0, 0);

	vertTerrain[(row + col * MAPSIZE) * 4 + 0].texCoords = sf::Vector2f(texMap[build].x     , texMap[build].y);
	vertTerrain[(row + col * MAPSIZE) * 4 + 1].texCoords = sf::Vector2f(texMap[build].x + 64, texMap[build].y);
	vertTerrain[(row + col * MAPSIZE) * 4 + 2].texCoords = sf::Vector2f(texMap[build].x + 64, texMap[build].y + 64);
	vertTerrain[(row + col * MAPSIZE) * 4 + 3].texCoords = sf::Vector2f(texMap[build].x     , texMap[build].y + 64);
}


//may be updated to accomodate more resources
//holds in order iron, coal, wood
//this does not transfer any resources, just displays them
std::vector<int> TileMap::getResources()
{
	std::vector<int> vect(5,0);
	
	for (WarehouseTile* warehouse : warehouseTiles)
	{
		for (auto& res : warehouse->getStoredResources())
		{
			//id offset by 10
			vect[res.first - 10] += res.second;
		}
	}
	return vect;


}


void TileMap::attemptNewWarehouseConnection(WarehouseTile* newWarehouse)
{
	auto itr = unconnectedResourceTiles.begin();
	while (itr != unconnectedResourceTiles.end())
	{
		ResourceTile* temp = *itr;
		if (canConnect(temp, newWarehouse))
		{
			temp->connectToWarehouse(newWarehouse);
			newWarehouse->addResourceTile(temp);
			resourceTiles.push_back(temp);
			itr = unconnectedResourceTiles.erase(itr);
			std::cout << "unconnected resource tile was connected to a new Warehouse" << std::endl;
		}
		else
			itr++;
	}

}



//destroying a developed tile
//remove tile from vector of unconnected or connected resources
//if connected, remove from resource tile vector of warehouse tile
//return tile type to original 
void TileMap::destroyTile(int row, int col, int id)
{
	ResourceTile* resource = (ResourceTile*)map[row][col];
	
	if (resource->isConnected())
	{
		//remove from resource tiles
		removeFromVector(resource, resourceTiles);

		//remove from warehouse resources
		WarehouseTile* warehouseptr = (WarehouseTile*)resource->getWarehousePtr();
		removeFromVector((Tile*)resource, warehouseptr->getResourceVect());
		
	}
	else
	{
		//remove from unconnectedresource tiles
		removeFromVector(resource, unconnectedResourceTiles);
	}
	map[row][col] = new LandTile(resource->getId() - 10,resource->getPosition());
	setTileTexture(row, col, map[row][col]->getId());
	delete resource;
}


//destroying warehouse
//remove from warehouse tile vector in tilemap
//disconnect all connected resources
//attempt to reconnect all connected resoures to other warehouses
void TileMap::destroyWareHouse(int row, int col, int id)
{
	WarehouseTile* warehouse = (WarehouseTile*)map[row][col];
	
	//remove from tileMap vector
	removeFromVector(warehouse, warehouseTiles);

	for (Tile* tile : warehouse->getResourceVect())
	{
		ResourceTile* temp = (ResourceTile*)tile;
		temp->disconnect();
		bool reconnected = false;
		for (auto newWarehouse : warehouseTiles)
		{
			if (canConnect(temp, newWarehouse) && !reconnected)
			{
				temp->connectToWarehouse(newWarehouse);
				newWarehouse->addResourceTile(temp);
				reconnected = true;
			}
			else //unable to connect resource
			{
				removeFromVector(temp,resourceTiles);
				unconnectedResourceTiles.push_back(temp);
			}
		}
	}
	map[row][col] = new LandTile(warehouse->getUndevelopedId(),warehouse->getPosition());
	setTileTexture(row, col, map[row][col]->getId());
	delete warehouse;
}


//destroying road is a little tricky
//current solution is just to check to see if all warehouses can still connect to all resources whenever a road is destroyed
//this is pretty inefficient, and would be stupid at scale
//later improvement to only check warehouses that can be found when exploring from current road
void TileMap::destroyRoad(int row, int col, int id)
{
	RoadTile* temp = (RoadTile*)map[row][col];
	map[row][col] = new LandTile(temp->getOriginalTile(),temp->getPosition());
	setTileTexture(row, col, map[row][col]->getId());

	//time to do the mother of all brute force
	for (auto warehouse : warehouseTiles)
	{
		std::cout << "iterating over Warehouses" << std::endl;
		for (auto connectedTile : warehouse->getResourceVect())
		{
			std::cout << "Iterating over resources connected to warehouse" << std::endl;
			ResourceTile* temp = (ResourceTile*)connectedTile;
			//destroying road severed connected
			if (!canConnect(connectedTile, warehouse))
			{
				std::cout << "Connection was severed" << std::endl;
				//disconnect and remove from warehouse connection
				temp->disconnect();
				removeFromVector((Tile*)temp, warehouse->getResourceVect());

				bool reconnected = false;
				for (auto newWarehouse : warehouseTiles)
				{
					if (canConnect(connectedTile, newWarehouse) && !reconnected)
					{
						ResourceTile* temp = (ResourceTile*)connectedTile;
						temp->connectToWarehouse(newWarehouse);
						newWarehouse->addResourceTile(temp);
						reconnected = true;
					}
				}
				if (!reconnected)
				{
					removeFromVector(temp, resourceTiles);
					unconnectedResourceTiles.push_back(temp);
				}
			}
			else
				std::cout << "still able to connect" << std::endl;
			
		}
	}
}


template<typename TILETYPE>
void TileMap::removeFromVector(TILETYPE* tile, std::vector<TILETYPE*>& vector)
{
	auto itr = vector.begin();
	while (itr != vector.end())
	{
		TILETYPE* accessItr = *itr;
		if (accessItr == tile)
		{
			itr = vector.erase(itr);
		}
		else
			itr++;
	}

}

//this function is known to be possible
void TileMap::removeFromWarehouses(int id, int amount)
{
	int cur = amount;
	int itr = 0;
	while (cur > 0)
	{
		if (itr == warehouseTiles.size())
			itr = 0;
		if (warehouseTiles[itr]->decreaseResource(id, 1)) //if this is possible
		{
			cur--;
		}
		itr++;
	}
}


//this function is not
bool TileMap::addToWarehouses(int id, int amount)
{
	int cur = amount;
	int itr = 0;
	//if unable to add to any of them, without this check this will loop forever
	bool possible = false;
	while (cur > 0)
	{
		if (itr == warehouseTiles.size())
		{
			if (possible)
			{
				itr = 0;
				possible = false;
			}
			else
				return false;
		}
			

		if (warehouseTiles[itr]->increaseResource(id, 1))
		{
			cur--;
			possible = true;
		}
		itr++;
	}
	return true;
}