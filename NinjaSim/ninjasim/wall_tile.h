#pragma once

#include "tile.h"

namespace NinjaSim
{
class WallTile: public Tile
{
public:
    WallTile(char letter):
        Tile(TileType::WALL, letter)
    {
    }

    virtual bool isObstacle() const
    {
        return true;
    }
};
}

