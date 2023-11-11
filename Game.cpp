#include "Game.h"
#include <time.h>
#include <random>
#include <iostream>


//chrono syntax wrappers
using clock_type = std::chrono::steady_clock;
using seconds_cast = std::chrono::duration<double, std::chrono::seconds::period>;
using time_point = std::chrono::steady_clock::time_point;


Game::Game()
{
    srand(time(NULL));
    initTextures();
    //documentation is also in HUD
    //0 is money, 1 is coal, 2 is wood, 3 is iron, 4 is fish
    playerAssets.resize(5);
    playerAssets[0] = 5000;
    hud.updateAssetValues(playerAssets);

    buttonSetUp();

    regionMaps[0] = new TileMap();
    system("CLS");

    // uncomment to skip the region chosing screen
    regionSelected = false;

    titleSprite.setOrigin(titleSprite.getGlobalBounds().width / 2, titleSprite.getGlobalBounds().height / 2);
    titleSprite.setScale(2, 2);

    titleMusic.openFromFile("Assets/titleScreenMusic.ogg");
    
    tutorialLetter.setSize(sf::Vector2f(800, 390));
    tutorialLetter.setOrigin(400, 195);
    tutorialLetter.setPosition(500, 300);
    tutorialLetter.setTexture(&assetHandler.textures.get("letter"), true);
}

Game::~Game()
{
    for (TileMap* map : regionMaps)
        if (map != nullptr)
            delete map;
}

void Game::initTextures()
{
    //sending stored textures to hud for use in sprites
    std::vector<sf::Texture*> hudTextVect;
    hudTextVect.push_back(&assetHandler.textures.get("HUD_Money"));
    hudTextVect.push_back(&assetHandler.textures.get("HUD_Coal"));
    hudTextVect.push_back(&assetHandler.textures.get("HUD_Wood"));
    hudTextVect.push_back(&assetHandler.textures.get("HUD_Iron"));
    hudTextVect.push_back(&assetHandler.textures.get("HUD_Fish"));
    hud.assignTextures(hudTextVect);
    hud.setFont(&assetHandler.fonts.get("basic"));

    titleSprite.setTexture(assetHandler.textures.get("title"));
}

void Game::runGame()
{
    w.create(sf::VideoMode(1000, 600), "Game Window");
    view.setZoom(std::min(w.getSize().x * 0.9, w.getSize().y * 0.8) / 1000);
    auto curTime = clock_type::now();
    auto startTime = clock_type::now();

    while (w.isOpen())
    {
        sf::Event event;
        while (w.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                w.close();
            if (event.type == sf::Event::Resized)
            {
                if (w.getSize().x < 1000) // Minimum window size to not ruin hud
                {
                    w.setSize(sf::Vector2u(1000, event.size.height));
                    sf::FloatRect visableArea(0, 0, 1000, event.size.height);
                    tutorialLetter.setPosition(500, event.size.height / 2);
                    w.setView(sf::View(visableArea));
                }

                else
                {
                    sf::FloatRect visableArea(0, 0, event.size.width, event.size.height);
                    tutorialLetter.setPosition(event.size.width / 2, event.size.height / 2);
                    w.setView(sf::View(visableArea));
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (regionSelected && !over)
                    {
                        int* calanderRef = hud.getCalander();
                        if (calanderRef[0] == 10 && calanderRef[1] == 29 && calanderRef[2] == 1929) //end game
                        {
                            if (playerAssets[0] >= 30000)
                            {
                                won = true;
                                over = true;
                            }
                        }

                        if (overlayOpen || tutorial) //Market and Tutorial take priority
                        {
                            if (marketOverlays.size() == 1)
                            {
                                tradeResource(marketOverlays[0]->buttonPressed(mouse.getPosition(w).x, mouse.getPosition(w).y));

                                if (marketOverlays[0]->closeCheck(mouse.getPosition(w).x, mouse.getPosition(w).y)) // close overlay
                                {
                                    overlayOpen = false;
                                    marketOverlays.pop_back();
                                }

                            }
                            else
                            {
                                if (tutorialLetter.getGlobalBounds().contains(mouse.getPosition(w).x, mouse.getPosition(w).y))
                                {
                                    int clickOffsetX = mouse.getPosition(w).x - tutorialLetter.getPosition().x;
                                    int clickOffsetY = mouse.getPosition(w).y - tutorialLetter.getPosition().y;

                                    if (clickOffsetY < -115) // titlebar like space 300x30
                                    {
                                        if (tutorialLetter.getSize().x - clickOffsetX < 430) // top right corner 30x30
                                            tutorial = false; // Close
                                    }
                                }
                            }

                        }

                        else if (mouse.getPosition(w).y < 100) // Then check if Hud is pressed
                            hud.buttonUpdate(sf::Vector2f(mouse.getPosition(w).x, mouse.getPosition(w).y));

                        else
                        {
                            button = false;
                            holdCheck = popUpManager.PopUpHoldCheck(mouse.getPosition(w).x, mouse.getPosition(w).y); // update held pop up



                            if (popUpManager.getPopUpNum() > 0) // check for button click on held pop up if one exists 
                            {
                                tempTileCord = popUpManager.getTilePos();
                                int oldID = regionMaps[0]->getMap()[tempTileCord.y][tempTileCord.x]->getId();
                                int newID = popUpManager.ButtonPressed(mouse.getPosition(w).x, mouse.getPosition(w).y);
                                std::cout << newID << '\n';
                                if (newID == -1 && playerAssets[0] > 100) //Road
                                {
                                    regionMaps[0]->buildRoad(tempTileCord.y, tempTileCord.x, newID);
                                    playerAssets[0] -= 100;
                                    hud.updateAssetValues(playerAssets);
                                    button = true;
                                }

                                if (newID == -2 && playerAssets[0] > 500) //Warehouse
                                {
                                    regionMaps[0]->buildWareHouse(tempTileCord.y, tempTileCord.x, newID);
                                    playerAssets[0] -= 500;
                                    hud.updateAssetValues(playerAssets);
                                    button = true;
                                }

                                if (newID >= 10 && playerAssets[0] > (250 * (newID / 10))) //Developed tile
                                {
                                    if (newID < 20) //developed first time
                                    {
                                        regionMaps[0]->developTile(tempTileCord.y, tempTileCord.x, newID);

                                    }
                                    else //upgrading
                                    {
                                        regionMaps[0]->upgradeTile(tempTileCord.y, tempTileCord.x);
                                    }
                                    playerAssets[0] -= (250 * (newID / 10));
                                    hud.updateAssetValues(playerAssets);
                                    button = true;

                                }

                                if (newID > -1 && newID < 10) //Destroyed Development
                                {

                                    if (newID == 8) //is a warehouse
                                        regionMaps[0]->destroyWareHouse(tempTileCord.y, tempTileCord.x, oldID);
                                    else
                                        regionMaps[0]->destroyTile(tempTileCord.y, tempTileCord.x, oldID);
                                    button = true;

                                }

                                if (newID == -10 && oldID == -1) //is a road
                                {
                                    regionMaps[0]->destroyRoad(tempTileCord.y, tempTileCord.x, oldID);
                                    button = true;
                                }

                                if (button)
                                    popUpManager.RemovePopUp();
                            }


                            sf::FloatRect bounds1 = buttons[0]->getBounds();
                            sf::FloatRect bounds2 = buttons[1]->getBounds();
                            if (bounds1.contains(sf::Vector2f(mouse.getPosition(w))))
                            {
                                marketOverlays.push_back(new MarketPopUp(mouse.getPosition(w).x, mouse.getPosition(w).y, market));
                                overlayOpen = true; //Stops game when open
                            }
                            else if (bounds2.contains(sf::Vector2f(mouse.getPosition(w))))
                            {
                                tutorial = true;
                            }

                            else if (holdCheck == 1) // check if holding a popUp
                                held = true;
                            else if (holdCheck == 0 && (mouse.getPosition(w).x > 100 || mouse.getPosition(w).y > 150)) // only make popUp if not holding one
                                regionMaps[0]->clickCheck(sf::Vector2f(mouse.getPosition(w)), w, view.getZoom(), view.getOffset(), regionMaps[0]->getMapSize(), &popUpManager);
                        }
                    }

                }
            }

            if (over)
            {
                if (won)
                    std::cout << "YOU WIN" << std::endl;
                playerAssets = std::vector<int>(5, 0);
                playerAssets[0] = 5000;
                delete regionMaps[0];
                regionMaps[0] = new TileMap();

                titleScreen();
            }


            if (!(sf::Mouse::isButtonPressed(sf::Mouse::Left))) // Drop popUp if mouse not pressed
            {
                held = false;
            }

            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    zoom = event.mouseWheelScroll.delta;
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Left:
                    left = true;
                    break;
                case sf::Keyboard::Right:
                    right = true;
                    break;
                case sf::Keyboard::Up:
                    up = true;
                    break;
                case sf::Keyboard::Down:
                    down = true;
                    break;
                case sf::Keyboard::R:
                    view.setZoom(std::min(w.getSize().x * 0.9, w.getSize().y * 0.8) / 1000);
                    view.setOffset(0, 0);
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Left:
                    left = false;
                    break;
                case sf::Keyboard::Right:
                    right = false;
                    break;
                case sf::Keyboard::Up:
                    up = false;
                    break;
                case sf::Keyboard::Down:
                    down = false;
                    break;
                }
            }
        }

        auto timeCheck = clock_type::now();
        auto deltaTime = timeCheck - curTime;
        //auto deltaResTime = timeCheck - resourceTime;
        double diff = std::chrono::duration_cast<seconds_cast>(deltaTime).count();
        //double resDiff = std::chrono::duration_cast<seconds_cast>(deltaResTime).count();




        if (hud.getGameSpeed() != 0)
        {
            //Timer Replaced with a month tick that toggles itself false whenever returns true
            if (hud.getMonthTick())
            {
                regionMaps[0]->updateResourceTiles();
                updatePlayerAssets();
                market.calculateNewPrices();
                hud.updateAssetValues(playerAssets);
            }


            if (diff > 1.0 / hud.getGameSpeed())
            {
                curTime = clock_type::now();
                int timeSinceStart = std::chrono::duration_cast<seconds_cast>(curTime - startTime).count() / 5;
                hud.updateTime();
            }
        }
        else //reset timer  if paused
            curTime = clock_type::now();


        now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
        if (last == 0)
            last = now;
        lag += now - last;
        last = now;

        while (lag >= 1000 / 30)
        {
            lag -= 1000 / 30;
            view.changeOffset((int(left) - int(right)) * 5, (int(up) - int(down)) * 5, regionMaps[0]->getMapSize());
            view.changeZoom(zoom);
            zoom = 0;
        }

        if (held) //Move popUp when held
        {
            popUpManager.MoveHeldPopUp(mouse.getPosition(w).x, mouse.getPosition(w).y);
        }


        w.clear();
        if (regionSelected)
        {
            animator.drawTileMap(regionMaps[0]->getMap(), w, view.getZoom(), regionMaps[0]->getMapSize(), view.getOffset(), sf::Vector2f(mouse.getPosition(w)), regionMaps[0]->getVertexTerrain(), assetHandler);
            popUpManager.UpdatePopUps(w);
            animator.drawHud(hud, w);

            w.draw(*buttons[0]);
            w.draw(*buttons[1]);

            if (marketOverlays.size() == 1)
                marketOverlays[0]->draw(w);
        }
        else
        {
            for (auto& region : regions)
            {
                sf::IntRect rect(region.getGlobalBounds().left + w.getSize().x / 2.0,
                    region.getGlobalBounds().top + w.getSize().y / 2.0, region.getGlobalBounds().width,
                    region.getGlobalBounds().height);
                if (rect.contains(mouse.getPosition(w)))
                {
                    region.setFillColor(sf::Color::Yellow);
                    if (mouse.isButtonPressed(sf::Mouse::Left))
                    {
                        tutorial = true;
                        regionSelected = true;
                    }
                }
                else
                {
                    region.setFillColor(sf::Color::White);
                }
            }
            animator.drawRegionMap(w, regions);
        }

        if (tutorial)
            w.draw(tutorialLetter);

        w.display();
    }
}

void Game::titleScreen()
{
    w.create(sf::VideoMode(800, 600), "Gilded Empires");
    w.clear(sf::Color::White);
    
    titleSprite.setPosition(w.getSize().x / 2, w.getSize().y / 2);
    titleMusic.play();
    titleMusic.setLoop(true);
    
    sf::RectangleShape base(sf::Vector2f(100, 50));
    base.setFillColor(sf::Color(128, 128, 128));
    base.setOutlineColor(sf::Color::Black);
    base.setOutlineThickness(5);
    std::string text = "PLAY";
    Button playButton = Button(text, 1, assetHandler.fonts.get("basic"), base);
    playButton.setOrigin(playButton.getBounds().width / 2, playButton.getBounds().height / 2);
    playButton.setPosition(w.getSize().x / 2, w.getSize().y * .8);

    while (w.isOpen())
    {
        sf::Event e;
        while (w.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                w.close();
                titleMusic.stop();
            }
            if (e.type == sf::Event::KeyPressed)
            {
                if (e.key.code == sf::Keyboard::Enter)
                {
                    w.close();
                    titleMusic.stop();
                    runGame();
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (playButton.getBounds().contains(sf::Vector2f(sf::Mouse::getPosition(w))))
                {
                    w.close();
                    titleMusic.stop();
                    runGame();
                }
            }
            if (e.type == sf::Event::Resized)
            {
                sf::FloatRect visableArea(0, 0, e.size.width, e.size.height);
                w.setView(sf::View(visableArea));
                playButton.setPosition(w.getSize().x / 2, w.getSize().y * .8);
                titleSprite.setPosition(w.getSize().x / 2, w.getSize().y / 2);

            }
        }
        w.clear(sf::Color::White);
        w.draw(titleSprite);
        w.draw(playButton);
        w.display();
    }
}

void Game::updatePlayerAssets()
{
    int money = playerAssets[0];
    playerAssets = std::vector<int>(5, 0);
    playerAssets[0] = money;
    for (int i = 0; i < 5; i++)
    {
        if (regionMaps[i] != nullptr)
        {
            //coal
            playerAssets[1] += regionMaps[i]->getResources()[1];
            //wood
            playerAssets[2] += regionMaps[i]->getResources()[2];
            //iron
            playerAssets[3] += regionMaps[i]->getResources()[3];
            //fish
            playerAssets[4] += regionMaps[i]->getResources()[4];
          
        }
    }
}

void Game::buttonSetUp()
{
    float scale = 1.5;

    buttonBase.resize(2);

    //Set Up Market Button
    buttonBase[0].setSize(sf::Vector2f(50, 50));
    buttonBase[0].setPosition(sf::Vector2f(3, 103));
    buttonBase[0].setFillColor(sf::Color::White);
    buttonBase[0].setOutlineColor(sf::Color::Black);
    buttonBase[0].setOutlineThickness(3);

    //Set up Tips Button
    buttonBase[1].setSize(sf::Vector2f(50, 50));
    buttonBase[1].setPosition(sf::Vector2f(56, 103));
    buttonBase[1].setFillColor(sf::Color::White);
    buttonBase[1].setOutlineColor(sf::Color::Black);
    buttonBase[1].setOutlineThickness(3);


    buttons.push_back(new Button(" ", -10, assetHandler.fonts.get("basic"), buttonBase[0],
        &assetHandler.textures.get("Market"), sf::IntRect(0,0,200,200)));

    buttons.push_back(new Button(" ", -15, assetHandler.fonts.get("basic"), buttonBase[1],
        &assetHandler.textures.get("Tutorial"), sf::IntRect(0, 0, 200, 200)));


    // still need regions to scale
    regions.resize(5);

    regions[0].setTexture(&assetHandler.textures.get("regionMap"));
    regions[0].setTextureRect(sf::IntRect(17, 19, 189, 245)); // North West
    regions[0].setSize(sf::Vector2f(189 * scale, 245 * scale));
    regions[0].setOrigin(regions[0].getSize().x / 2.0, regions[0].getSize().y / 2.0);
    regions[0].setPosition(-213, -90);

    regions[1].setTexture(&assetHandler.textures.get("regionMap"));
    regions[1].setTextureRect(sf::IntRect(324, 76, 195, 154)); // South
    regions[1].setSize(sf::Vector2f(195 * scale, 154 * scale));
    regions[1].setOrigin(regions[1].getSize().x / 2.0, regions[1].getSize().y / 2.0);
    regions[1].setPosition(-50, 100);

    regions[2].setTexture(&assetHandler.textures.get("regionMap"));
    regions[2].setTextureRect(sf::IntRect(696, 76, 195, 161)); // South East
    regions[2].setSize(sf::Vector2f(195 * scale, 161 * scale));
    regions[2].setOrigin(regions[2].getSize().x / 2.0, regions[2].getSize().y / 2.0);
    regions[2].setPosition(213, 90);

    regions[3].setTexture(&assetHandler.textures.get("regionMap"));
    regions[3].setTextureRect(sf::IntRect(1071, 72, 140, 144)); // North East
    regions[3].setSize(sf::Vector2f(140 * scale, 144 * scale));
    regions[3].setOrigin(regions[3].getSize().x / 2.0, regions[3].getSize().y / 2.0);
    regions[3].setPosition(320, -135);

    regions[4].setTexture(&assetHandler.textures.get("regionMap"));
    regions[4].setTextureRect(sf::IntRect(1336, 61, 247, 149)); // North
    regions[4].setSize(sf::Vector2f(247 * scale, 149 * scale));
    regions[4].setOrigin(regions[4].getSize().x / 2.0, regions[4].getSize().y / 2.0);
    regions[4].setPosition(58, -120);
}

void Game::tradeResource(int resource)
{
    int changedAssetNum;
    int amountChange;
    std::vector<int> prices = market.getPrices();

    updatePlayerAssets();

    if (resource == -1)
    {
        std::cout << "NO RESOURCE\n";
        return;
    }

    if (resource % 12 < 3) //Coal
        changedAssetNum = 1;
    else if (resource % 12 < 6) //Wood
        changedAssetNum = 2;
    else if (resource % 12 < 9) //Iron
        changedAssetNum = 3;
    else if (resource % 12 < 12) //Fish
        changedAssetNum = 4;

    switch (resource % 3)
    {
    case 0:
        amountChange = 1;
        break;
    case 1:
        amountChange = 5;
        break;
    case 2:
        amountChange = 50;
        break;
    }

    std::cout << (prices[(changedAssetNum - 1) * 2] * amountChange) << '\n' << playerAssets[0] << '\n';

    if (resource < 12 && (playerAssets[0] >= (prices[(changedAssetNum - 1) * 2] * amountChange)))
    {
        if (regionMaps[0]->addToWarehouses(changedAssetNum + 10, amountChange))
        {
            regionMaps[0]->removeFromWarehouses(changedAssetNum + 10, amountChange);

            playerAssets[0] -= prices[(changedAssetNum - 1) * 2] * amountChange;
            updatePlayerAssets();

            market.newTransaction(resource, amountChange);
        }

    }
     else if(playerAssets[changedAssetNum] >= amountChange && resource >= 12)
    {
        playerAssets[0] += prices[(changedAssetNum - 1) * 2 + 1] * amountChange;
        

        regionMaps[0]->removeFromWarehouses(changedAssetNum + 10, amountChange);
        updatePlayerAssets();
        market.newTransaction(resource, amountChange);
    }   


    hud.updateAssetValues(playerAssets);
}