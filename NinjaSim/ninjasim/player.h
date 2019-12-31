#pragma once

#include <QPoint>
#include <QPointer>
#include <QSharedPointer>
#include <QStringList>
#include <QTextStream>
#include <QVector>

#include "direction.h"
#include "tile.h"

namespace NinjaSim
{
class Simulation;

class Player
{
public:
    Player();

    QString runStep();

    QStringList actionList() const;

    QPoint position() const;
    QPoint direction() const;

    QVector<QPoint> possibleDirections() const;
    void resetDirectionPriorities();
    void reverseDirectionPriorities();

    bool dead() const;
    quint32 shurikens() const;
    bool breakerMode() const;

    friend QTextStream& operator<<(QTextStream& out, const Player& p);

private:

    void setSimulation(Simulation* simulation);
    void setPosition(const QPoint& position);
    void setDirection(const QPoint& direction);
    void setDead(bool dead);
    void setShurikens(quint32 shurikens);
    void setBreakerMode(bool breakerMode);

    QString addAction(QString action);
    QString move(QPoint destination, QPoint direction);
    QString throwShuriken(QSharedPointer<Tile> target);

private:

    friend class Simulation;

    QPointer<Simulation> m_simulation;

    QPoint m_position;
    QPoint m_direction;
    // Helper variable to easily print player state
    bool m_defaultPriorities;
    QVector<QPoint> m_directionPriorities;

    quint32 m_shurikens;
    bool m_breakerMode;
    bool m_dead;

    QStringList m_actionList;
};
}




