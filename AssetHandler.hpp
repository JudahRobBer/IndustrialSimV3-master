#pragma once
#include "AssetLoader.hpp"

//Look here for resource names
class AssetHandler
{
public:
	AssetHandler()
	{
		initFonts();
		initTextures();
		initTextRects();
	}
	~AssetHandler()
	{

	}

	//hold seperate texture files
	AssetLoader<sf::Font> fonts;
	AssetLoader<sf::Texture> textures;
	AssetLoader<sf::Texture> tileTextures;
	

	//holds intRects within texture file
	std::unordered_map < std::string, sf::IntRect> textRects;
	
private:
	void initFonts()
	{
		fonts.load("basic", "Textures/PixelGameFont.ttf");
	}

	void initTextures()
	{
		
		textures.load("popUp", "Textures/popUp.png");
		textures.load("popUpShort", "Textures/popUpShort.png");
		textures.load("popUpLong", "Textures/popUpLong.png");
		textures.load("HUD_Money", "Textures/HUD_Money.png");
		textures.load("HUD_Coal", "Textures/HUD_Coal.png");
		textures.load("HUD_Wood", "Textures/HUD_Wood.png");
		textures.load("HUD_Iron", "Textures/HUD_Iron.png");
		textures.load("HUD_Fish", "Textures/HUD_Fish.png");
		textures.load("Market", "Textures/Market.png");
		textures.load("Tutorial", "Textures/Tutorial.png");
		textures.load("ButtonSpriteSheet", "Textures/buttonSpriteSheet.png");
		textures.load("tileMap", "Textures/tileMap.png");
		textures.load("buildMap", "Textures/tileMap.png");
		textures.load("timeButtons", "Textures/time_textures.png");
		textures.load("regionMap", "Textures/regionMap.png");
		textures.load("title", "Textures/Title.png");
		textures.load("letter", "Textures/Tutorial_Letter.png");
	}

	void initTileTextures()
	{

	}

	void initTextRects()
	{
		sf::IntRect textSize = { 0, 0, 1440, 81 };
		textRects["upgradeButton"] = { 484,4,308,349 };
		textRects["roadButton"] = sf::IntRect(0, 69, 380, 260);
		textRects["wareHouseButton"] = sf::IntRect(940, 100, 310, 200);
		textRects["pause"] = sf::IntRect(0, 0, 100, 100);
		textRects["1speed"] = sf::IntRect(100, 0, 100, 100);
		textRects["3speed"] = sf::IntRect(200, 0, 100, 100);
		textRects["10speed"] = sf::IntRect(300, 0, 100, 100);
	}

};