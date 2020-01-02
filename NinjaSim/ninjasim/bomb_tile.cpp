#include "bomb_tile.h"
#include "simulation.h"

namespace NinjaSim
{

BombTile::BombTile(char letter):
    Tile(TileType::BOMB, letter),
    m_counter(QString(letter).toInt()),
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

int BombTile::counter() const
{
    return m_counter;
}

void BombTile::setCounter(int counter)
{
    m_counter = counter;
    // Update the tile letter
    setLetter(QString::number(counter).at(0).toLatin1());
}

void BombTile::runStep(Simulation* simulation)
{
    if (!m_activated || m_detonated)
        return;

    if (m_counter > 0)
    {
        // Decrease the counter
        setCounter(m_counter - 1);
    }

    // Detonate when the counter reaches zero
    if (m_counter == 0)
    {
        detonate(simulation);
    }
}

void BombTile::detonate(Simulation* simulation)
{
    if (m_detonated)
        return;

    m_detonated = true;
    setCounter(0);

    // Try all 4 directions
    for (QPoint dir : Direction::all())
    {
        // Start from the bomb position
        QPoint targetPos = position();

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
            // The Holy Symbol also functions as an indestructible obstacle
            // when considering the explosion
            if (target->type() == TileType::GOAL)
                break;

            // Check if this tile is destructible (or a shuriken)
            if (target->isDestructible() ||
                target->type() == TileType::SHURIKEN)
            {
                simulation->replaceTile(targetPos, ' ');
            }

            // Check if there are any players on this tile
            for (auto player : simulation->findPlayers(targetPos))
            {
                // Kill this player
                player->setDead(true);
            }

            if (target->type() == TileType::BOMB)
            {
                target.staticCast<BombTile>()->detonate(simulation);
            }
        }
    }
}

}

