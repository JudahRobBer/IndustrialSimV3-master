#include "PopUpManager.h"
#include <iostream>

PopUpManager::PopUpManager()
{
    heldPopUp = 0;
}

PopUpManager::~PopUpManager()
{
}

void PopUpManager::UpdatePopUps(sf::RenderWindow& window)
{
    // Draw in inverted order
    for (int i = CurrentPopUp.size() - 1; i >= 0; i--)
    {
        CurrentPopUp[i]->displayWindow(window);
    }
}

void PopUpManager::NewPopUp(int xPos, int yPos, int id, sf::Vector2f tilePos, int type)
{
    if (type == -1)
    {
        std::cout << "UNDEVELOPED\nPOSITION: " << tilePos.x << ',' << tilePos.y << "\nID: " << id << '\n';
        CurrentPopUp.push_back(new ConstructionPopUp(xPos, yPos, id, tilePos));
    }
    if (type == 0)
    {
        std::cout << "DEVELOPED\nPOSITION: " << tilePos.x << ',' << tilePos.y << "\nID: " << id << '\n';
        CurrentPopUp.push_back(new UpgradePopUp(xPos, yPos, id, tilePos));
    }
    if (type == 1)
    {
        std::cout << "ROAD\nPOSITION: " << tilePos.x << ',' << tilePos.y << "\nID: " << id << '\n';
        CurrentPopUp.push_back(new UpgradePopUp(xPos, yPos, id, tilePos));
    }
    if (type == 2)
    {
        std::cout << "WAREHOUSE\nPOSITION: " << tilePos.x << ',' << tilePos.y << "\nID: " << id << '\n';
        CurrentPopUp.push_back(new ConstructionPopUp(xPos, yPos, id, tilePos));
    }
}

void PopUpManager::RemovePopUp()
{
    delete CurrentPopUp[heldPopUp];
    CurrentPopUp.erase(CurrentPopUp.begin() + heldPopUp);
}

int PopUpManager::PopUpHoldCheck(int x, int y)
{
    for (int i = 0; i < CurrentPopUp.size(); i++)
    {
        if (CurrentPopUp[i]->windowCollision(x, y) == 2) //close
        {
            delete CurrentPopUp[i];
            CurrentPopUp.erase(CurrentPopUp.begin() + i);
            return 2;
        }
        else if (CurrentPopUp[i]->windowCollision(x, y) == 1) //held
        {
            heldPopUp = i;
            return 1;
        }
        else if (CurrentPopUp[i]->windowCollision(x, y) == 3) // other interactions, no new popup
        {
            heldPopUp = i;
            return 3;
        }
    }
    return 0; //not held, keep open
}

void PopUpManager::MoveHeldPopUp(int x, int y)
{
    CurrentPopUp[heldPopUp]->moveWindow(x, y);
}

int PopUpManager::ButtonPressed(int x, int y)
{
    return CurrentPopUp[heldPopUp]->buttonUpdate(x, y);
}

int PopUpManager::getPopUpNum()
{
    return CurrentPopUp.size();
}

sf::Vector2f PopUpManager::getTilePos()
{
    return CurrentPopUp[heldPopUp]->getTileCords();
}
