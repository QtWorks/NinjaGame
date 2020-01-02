#pragma once

#include "tile.h"

namespace NinjaSim
{
class BoxTile: public Tile
{
public:
    BoxTile(char letter):
        Tile(TileType::BOX, letter)
    {
    }

    virtual bool isObstacle() const
    {
        return true;
    }

    virtual bool isDestructible() const
    {
        return true;
    }
};
}

