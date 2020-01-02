#include "bomb_tile.h"
#include "simulation.h"

namespace NinjaSim
{

BombTile::BombTile(char letter):
    Tile(TileType::BOMB, letter),
    m_activated(false),
    m_detonated(false)
{
}

bool BombTile::isDynamic() const
{
    return true;
}

bool BombTile::activated() const
{
    return m_activated;
}

void BombTile::setActivated(bool activated)
{
    m_activated = activated;
}

void BombTile::runStep(Simulation* simulation)
{
    if (!m_activated || m_detonated)
        return;

    int counter = QString(m_letter).toInt();

    if (counter > 0)
    {
        // Decrease the counter and update the tile letter
        counter--;
        m_letter = QString::number(counter).at(0).toLatin1();
    }

    // Detonate when the counter reaches zero
    if (counter == 0)
    {
        detonate(simulation);
    }
}

void BombTile::detonate(Simulation* simulation)
{
    if (m_detonated)
        return;

    m_detonated = true;

    // Try all 4 directions
    for (QPoint dir : Direction::all())
    {
        // Start from the bomb position
        QPoint targetPos = m_position;

        // Detonate within a range of 2 tiles
        for (int i = 0; i < 2; i++)
        {
            // Move by one step in the given direction
            targetPos += dir;

            auto target = simulation->tile(targetPos);
            // Skip non-existent tiles that would be outside the map
            if (!target)
                break;

            // An indestructible obstacle can shield tiles from the bomb
            if (target->isObstacle() && !target->isDestructible())
                break;

            // Check if this tile is destructible (or a shuriken)
            if (target->isDestructible() ||
                target->type() == TileType::SHURIKEN)
            {
                simulation->replaceTile(targetPos, ' ');
            }

            if (target->type() == TileType::BOMB)
            {
                //target->detonate();
            }
        }
    }
}

}

