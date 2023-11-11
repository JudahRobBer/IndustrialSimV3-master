#pragma once

#include "DevelopedTile.h"
#include "LandTile.h"
#include "ResourceTile.h"
#include "WarehouseTile.h"
#include "RoadTile.h"
#include "TransportationTile.h"
#include "PopUpManager.h"
#include <vector>
#include <unordered_set>
#include <utility>



class TileMap
{
public:
	TileMap();
	~TileMap();

	std::vector<std::vector<Tile*>>& getMap();
	bool canConnect(Tile*, Tile*); //dfs traversal of transportationTiles

	void clickCheck(sf::Vector2f, sf::RenderWindow&, double, sf::Vector2f, int, PopUpManager* manager);
	void setDevelopmentType(int, int, int, int);
	int getMapSize();

	std::vector<int> getResources();

	void updateResourceTiles();

	sf::VertexArray& getVertexTerrain();

	void developTile(int, int, int);
	void buildWareHouse(int, int, int);
	void buildRoad(int, int, int);

	void destroyTile(int, int, int);
	void destroyWareHouse(int, int, int);
	void destroyRoad(int, int, int);

	//tile at location has an increased generated per turn
	void upgradeTile(int, int);

	void removeFromWarehouses(int, int); //this is always called after desired amount is confirmed to exist
	bool addToWarehouses(int, int); //this may not be possible given capacity of warehouses, thus returns boolean

	void updateTextures();
private:
	void initTerrain();

	//every time a new warehouse is developed,
	//check unconnected resources to see if a connection is possible
	void attemptNewWarehouseConnection(WarehouseTile*);
	
	//multipurpose utility function
	template<typename TILETYPE>
	void removeFromVector(TILETYPE*, std::vector<TILETYPE*>&);

	//for developing tiles
	void setTileTexture(int, int, int);

	bool isValid(bool[32][32], int, int);
	const int MAPSIZE = 32;
	std::vector<std::vector<Tile*>> map;

	//more efficiently iterate over just developed tiles when ticking
	std::vector<ResourceTile*> resourceTiles;

	//when a resource tile is first built, complete a search for a warehouse
	//if the search fails, add this resource tile to this vector
	//whenever a new road is built, run a warehouse search on the tiles in this vector
	std::vector<ResourceTile*> unconnectedResourceTiles;

	//used for when resource tiles are initially connected to a warehouse, search until one is found
	//also for checking total held resources
	std::vector<WarehouseTile*> warehouseTiles;

	//somewhere the ids of hills and water got switched, and im just rolling with it
	enum TERRAINTYPE { WATER = 0, PLAINS, FOREST, HILLS };
	enum RESOURCETYPE { FISH = 10, COAL, LUMBER, IRON };
	enum OTHERTILES { WAREHOUSE = -2, ROAD = -1 };

	sf::VertexArray vertTerrain;
};

