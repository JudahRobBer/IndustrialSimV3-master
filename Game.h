#pragma once
#include "Engine.h"
#include "TileMap.h"
#include "PopUps.h"
#include "View.h"
#include "Hud.h"
#include "Button.h"
#include "Market.h"
#include "MarketPopUp.h"
#include <chrono>
#include <vector>

class Game
{
public:
	Game();
	~Game();

	void runGame();
	void titleScreen();

private:
	AssetHandler assetHandler;
	Animator animator;
	PopUpManager popUpManager;
	sf::RenderWindow w;
	sf::Mouse mouse;
	View view;
	Hud hud;
	TileMap* regionMaps[5];
	
	sf::Sprite titleSprite;
	sf::Music titleMusic;

	//Market and Tip buttons
	std::vector<Button*> buttons;
	std::vector<sf::RectangleShape> buttonBase;

	std::vector<MarketPopUp*> marketOverlays;
	sf::RectangleShape tutorialLetter;

	std::vector<sf::RectangleShape> regions;

	Market market;

	sf::Vector2f tempTileCord;
	sf::Texture temp;

	int holdCheck = 0;
	double now = 0, last = 0, lag = 0;
	bool left = false, right = false, up = false, down = false, held = false, button = false, overlayOpen = false, regionSelected = true;
	double zoom = 0;
	bool won = false;
	bool over = false;
	bool tutorial = false;

	std::vector<int> playerAssets;

	void initTextures();
	void updatePlayerAssets();
	void buttonSetUp();
	void tradeResource(int);
};

