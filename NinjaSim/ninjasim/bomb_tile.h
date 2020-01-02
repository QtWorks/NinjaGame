#pragma once

#include "tile.h"

namespace NinjaSim
{
class BombTile: public Tile
{
public:
    BombTile(char letter);

    virtual bool isDynamic() const;

    virtual bool activated() const;
    virtual void setActivated(bool activated);

    virtual void runStep(Simulation* simulation);

private:

    void detonate(Simulation* simulation);

private:

    bool m_activated;
    bool m_detonated;
};
}

