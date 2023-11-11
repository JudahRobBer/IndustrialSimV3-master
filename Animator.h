#pragma once
#include "TileMap.h"
#include "Hud.h"
#include "SFML/Graphics.hpp"
class Animator
{
public:
	Animator();
	~Animator();


	void drawTileMap(std::vector<std::vector<Tile*>>&, sf::RenderWindow&, double, int, sf::Vector2f, sf::Vector2f, sf::VertexArray&, AssetHandler&);
	void drawHud(Hud&, sf::RenderWindow&);
	void drawRegionMap(sf::RenderWindow&, std::vector<sf::RectangleShape>&);

};

