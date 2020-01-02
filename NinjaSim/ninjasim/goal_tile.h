#pragma once

#include "tile.h"

namespace NinjaSim
{
class GoalTile: public Tile
{
public:
    GoalTile(char letter):
        Tile(TileType::GOAL, letter)
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

