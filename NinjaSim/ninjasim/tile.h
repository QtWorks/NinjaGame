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

    virtual QPoint direction() const;

    virtual QPoint pathwayEndpoint() const;
    virtual void setPathwayEndpoint(const QPoint& pathwayEndpoint);

    virtual bool activated() const;
    virtual void setActivated(bool activated);
    virtual void runStep(Simulation*);

protected:

    TileType m_type;
    char m_letter;

    // The position of this tile on the map
    QPoint m_position;
};
}

