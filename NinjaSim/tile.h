#pragma once

#include "tile_type.h"

#include <QPoint>

class Tile
{
public:
    Tile(TileType type = TileType::EMPTY, char letter = ' ');

    TileType type() const;
    char letter() const;

    bool isWalkable() const;
    bool isObstacle() const;
    bool isDestructible() const;


    QPoint direction() const;

    QPoint pathwayEndpoint() const;
    void setPathwayEndpoint(const QPoint& pathwayEndpoint);

private:

    TileType m_type;
    char m_letter;

    // Direction used for path modifier arrows
    QPoint m_direction;

    // The other endpoint for pathway
    QPoint m_pathwayEndpoint;
};

