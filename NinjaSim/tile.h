#pragma once

#include "tile_type.h"

#include <QPoint>

class Tile
{
public:
    Tile(TileType type = TileType::EMPTY, char letter = ' ');

    TileType type() const;
    char letter() const;

    bool isObstacle() const;
    bool isDestructible() const;

    QPoint direction() const;

    QPoint pathwayEndpoint() const;
    void setPathwayEndpoint(const QPoint& pathwayEndpoint);

    QPoint position() const;
    void setPosition(const QPoint& position);

private:

    TileType m_type;
    char m_letter;

    // The position of this tile on the map
    QPoint m_position;

    // Direction used for path modifier arrows
    QPoint m_direction;

    // The other endpoint for pathway
    QPoint m_pathwayEndpoint;
};

