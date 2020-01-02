#pragma once

#include "tile.h"

namespace NinjaSim
{
class ShurikenTile: public Tile
{
public:
    ShurikenTile(char letter):
        Tile(TileType::SHURIKEN, letter)
    {
    }
};
}

