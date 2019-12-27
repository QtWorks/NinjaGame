#pragma once

#include <QPoint>
#include <QPointer>
#include <QStringList>
#include <QVector>

#include "direction.h"

class Simulation;

class Player
{
public:
    Player();

    void setSimulation(Simulation* simulation);

    QString runStep();

    QPoint position() const;
    void setPosition(const QPoint& position);

    QPoint direction() const;
    void setDirection(const QPoint& direction);

    QVector<QPoint> possibleDirections();
    void resetDirectionPriorities();
    void reverseDirectionPriorities();

    bool dead() const;
    void setDead(bool dead);

    quint32 shurikens() const;
    void setShurikens(quint32 shurikens);

    bool breakerMode() const;
    void setBreakerMode(bool breakerMode);

    QStringList actionList() const;

private:

    QString move(QPoint destination, QPoint direction);

private:

    QPointer<Simulation> m_simulation;

    QPoint m_position;
    QPoint m_direction;
    QVector<QPoint> m_directionPriorities;

    quint32 m_shurikens;
    bool m_breakerMode;
    bool m_dead;

    QStringList m_actionList;

};

