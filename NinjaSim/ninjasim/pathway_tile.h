#pragma once

#include "tile.h"

namespace NinjaSim
{
class PathwayTile: public Tile
{
public:
    PathwayTile(char letter):
        Tile(TileType::PATHWAY, letter)
    {
    }

    virtual QPoint pathwayEndpoint() const
    {
        return m_pathwayEndpoint;
    }

    virtual void setPathwayEndpoint(const QPoint &pathwayEndpoint)
    {
        m_pathwayEndpoint = pathwayEndpoint;
    }

private:

    // The other endpoint for pathway
    QPoint m_pathwayEndpoint;
};
}

