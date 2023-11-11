#include "Animator.h"
#include "Hud.h"
#include <iostream>
#include <unordered_map>



Animator::Animator()
{

}

Animator::~Animator()
{

}


void Animator::drawTileMap(std::vector<std::vector<Tile*>>& mapRef, sf::RenderWindow& w, double zoom, int mapSize, sf::Vector2f offset, sf::Vector2f mousePos, sf::VertexArray& terrain, AssetHandler & assetHandler)
{
	sf::FloatRect boundingBox;
	sf::RectangleShape rect;
	sf::Vector2f coords, pos;
	bool hover = false;

	rect.setSize(sf::Vector2f(zoom * 100.0, zoom * 100.0));
	rect.setOutlineColor(sf::Color::White);
	rect.setFillColor(sf::Color(255, 255, 255, 64));
	rect.setOutlineThickness(7.0 * zoom);

	for (int x = 0; x < mapSize; x++)
		for (int y = 0; y < mapSize; y++)
		{
			coords = mapRef[x][y]->getPosition();
			pos = sf::Vector2f(
				w.getSize().x / 2.0 - mapSize * 50 * zoom + 100.0 * coords.x * zoom + offset.x, 
				w.getSize().y / 2.0 - mapSize * 50 * zoom + 100.0 * coords.y * zoom + offset.y);

			boundingBox = sf::FloatRect(pos.x, pos.y, 100.0 * zoom, 100.0 * zoom);
			if (boundingBox.contains(mousePos))
			{
				rect.setPosition(pos.x, pos.y);
				hover = true;
			}

			terrain[(x + y * mapSize) * 4 + 0].position = sf::Vector2f(pos.x, pos.y);
			terrain[(x + y * mapSize) * 4 + 1].position = sf::Vector2f(pos.x + zoom * 100.0, pos.y);
			terrain[(x + y * mapSize) * 4 + 2].position = sf::Vector2f(pos.x + zoom * 100.0, pos.y + zoom * 100.0);
			terrain[(x + y * mapSize) * 4 + 3].position = sf::Vector2f(pos.x, pos.y + zoom * 100.0);
		}

	w.draw(terrain, &assetHandler.textures.get("tileMap"));
	if (hover)
		w.draw(rect);

}

void Animator::drawHud(Hud& hud, sf::RenderWindow& w)
{
	hud.updateHudPosition(w.getSize().x);

	sf::RectangleShape* itemBar = hud.getItemBar();
	std::vector<sf::Sprite*> items = hud.getItems();
	std::vector<sf::Text*> textItems = hud.getTexts();
	std::vector<Button*> button = hud.getButton();


	//item bar
	w.draw(*itemBar);
	for (int i = 0; i < items.size(); i++)
		w.draw(*items[i]);
	for (int i = 0; i < textItems.size(); i++)
		w.draw(*textItems[i]);
	for (int i = 0; i < button.size(); i++)
		w.draw(*button[i]);
}

void Animator::drawRegionMap(sf::RenderWindow &w, std::vector<sf::RectangleShape> &regions)
{
	for (auto region : regions)
	{
		region.setPosition(w.getSize().x / 2.0 + region.getPosition().x, w.getSize().y / 2.0 + region.getPosition().y);
		w.draw(region);
	}
}
