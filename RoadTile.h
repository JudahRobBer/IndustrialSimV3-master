#pragma once
#include "DevelopedTile.h"

//this class is basically empty
class RoadTile :
    public DevelopedTile
{
public:
    RoadTile(int oldId)
    {
        id = -1;
        undevelopedId = oldId;
    }

    RoadTile(int oldId, sf::Vector2f pos)
    {
        id = -1;
        position = pos;
        undevelopedId = oldId;
    }

    ~RoadTile()
    {

    }

    int getOriginalTile()
    {
        return undevelopedId;
    }
private:
    int undevelopedId;
};

