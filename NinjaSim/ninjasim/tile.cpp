#include "tile.h"
#include "simulation.h"

namespace NinjaSim
{

Tile::Tile(TileType type, char letter):
    m_type(type),
    m_letter(letter)
{

}

Tile::~Tile()
{

}

TileType Tile::type() const
{
    return m_type;
}

char Tile::letter() const
{
    return m_letter;
}


QPoint Tile::position() const
{
    return m_position;
}

void Tile::setPosition(const QPoint &position)
{
    m_position = position;
}

bool Tile::isDynamic() const
{
    return false;
}

bool Tile::isObstacle() const
{
    return false;
}

bool Tile::isDestructible() const
{
    return false;
}

void Tile::runStep(Simulation*)
{
}

void Tile::setLetter(char letter)
{
    m_letter = letter;
}

}
