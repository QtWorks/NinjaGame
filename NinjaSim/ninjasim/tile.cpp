#include "tile.h"
#include "direction.h"

namespace NinjaSim
{

Tile::Tile(TileType type, char letter):
    m_type(type),
    m_letter(letter),
    m_direction(QPoint())
{
    if (m_type == TileType::ARROW)
    {
        switch (m_letter)
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
}

TileType Tile::type() const
{
    return m_type;
}

char Tile::letter() const
{
    return m_letter;
}

bool Tile::isObstacle() const
{
    switch (m_type)
    {
    case TileType::WALL:
    case TileType::BOX:
    case TileType::GOAL:
    case TileType::MIRROR:
        return true;

    default:
        return false;
    }
}

bool Tile::isDestructible() const
{
    switch (m_type)
    {
    case TileType::BOX:
    case TileType::GOAL:
        return true;

    default:
        return false;
    }
}

QPoint Tile::direction() const
{
    return m_direction;
}

QPoint Tile::pathwayEndpoint() const
{
    return m_pathwayEndpoint;
}

void Tile::setPathwayEndpoint(const QPoint &pathwayEndpoint)
{
    m_pathwayEndpoint = pathwayEndpoint;
}

QPoint Tile::position() const
{
    return m_position;
}

void Tile::setPosition(const QPoint &position)
{
    m_position = position;
}

}
