#pragma once

#include "tile.h"

namespace NinjaSim
{
class BombTile: public Tile
{
public:
    BombTile(char letter);

    virtual bool isDynamic() const;
    virtual void runStep(Simulation* simulation);

    bool activated() const;
    int counter() const;

private:

    void setActivated(bool activated);
    void setCounter(int counter);
    void detonate(Simulation* simulation);

private:

    friend class Simulation;

    int m_counter;

    bool m_activated;
    bool m_detonated;
};
}

