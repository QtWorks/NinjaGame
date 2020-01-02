#pragma once

#include "tile.h"

namespace NinjaSim
{
class MirrorTile: public Tile
{
public:
    MirrorTile(char letter):
        Tile(TileType::MIRROR, letter)
    {
    }

    virtual bool isObstacle() const
    {
        return true;
    }
};
}

