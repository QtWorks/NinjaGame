#pragma once

#include "tile.h"

namespace NinjaSim
{
class ArrowTile: public Tile
{
public:
    ArrowTile(char letter):
        Tile(TileType::ARROW, letter)
    {
        switch (letter)
        {
        case 'S':
            m_direction = Direction::south();
            break;
        case 'E':
            m_direction = Direction::east();
            break;
        case 'N':
            m_direction = Direction::north();
            break;
        case 'W':
            m_direction = Direction::west();
            break;
        default:
            Q_ASSERT(false && "Invalid direction letter");
            break;
        }
    }

    QPoint direction() const
    {
        return m_direction;
    }

private:

    // Direction used for path modifier arrows
    QPoint m_direction;
};
}

