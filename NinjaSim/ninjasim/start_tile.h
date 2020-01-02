#pragma once

#include "tile.h"

namespace NinjaSim
{
class StartTile: public Tile
{
public:
    StartTile(char letter):
        Tile(TileType::START, letter)
    {
    }
};
}

