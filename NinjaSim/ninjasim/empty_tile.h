#pragma once

#include "tile.h"

namespace NinjaSim
{
class EmptyTile: public Tile
{
public:
    EmptyTile(char letter):
        Tile(TileType::EMPTY, letter)
    {
    }
};
}

