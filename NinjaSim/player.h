#pragma once

#include <QPoint>
#include <QVector>

#include "direction.h"

class Player
{
public:
    Player();

    QPoint position() const;
    void setPosition(const QPoint &position);

    QPoint direction() const;
    void setDirection(const QPoint &direction);

    QPoint followNextDirection();
    void resetDirectionPriorities();
    void reverseDirectionPriorities();

    bool alive() const;
    void setAlive(bool alive);

    quint32 shurikens() const;
    void setShurikens(const quint32 &shurikens);

    bool breakerMode() const;
    void setBreakerMode(bool breakerMode);

private:

    QPoint m_position;
    QPoint m_direction;
    QVector<QPoint> m_directionPriorities;

    quint32 m_shurikens;
    bool m_breakerMode;
    bool m_alive;
};

