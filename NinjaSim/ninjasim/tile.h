#pragma once

#include "direction.h"
#include "tile_type.h"

#include <QPoint>

namespace NinjaSim
{
class Simulation;

class Tile
{
protected:
    // A protected constructor to avoid direct instantiation of Tile objects
    Tile(TileType type, char letter);

public:
    virtual ~Tile();

    TileType type() const;
    char letter() const;

    QPoint position() const;
    void setPosition(const QPoint& position);

    virtual bool isDynamic() const;
    virtual bool isObstacle() const;
    virtual bool isDestructible() const;

    virtual void runStep(Simulation*);

protected:

    void setLetter(char letter);

private:

    TileType m_type;
    char m_letter;

    // The position of this tile on the map
    QPoint m_position;
};
}

