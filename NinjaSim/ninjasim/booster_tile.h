#pragma once

#include "tile.h"

namespace NinjaSim
{
class BoosterTile: public Tile
{
public:
    BoosterTile(char letter):
        Tile(TileType::BOOSTER, letter)
    {
    }
};
}

