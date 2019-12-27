#pragma once

#include <QPoint>
#include <QString>

class Direction
{
public:

    static QPoint south() { return QPoint(0,1); }
    static QPoint east() { return QPoint(1,0); }
    static QPoint north() { return QPoint(0,-1); }
    static QPoint west() { return QPoint(-1,0); }

    static QString name(QPoint dir)
    {
        if (dir == south())
            return "SOUTH";
        else if (dir == east())
            return "EAST";
        else if (dir == north())
            return "NORTH";
        else if (dir == west())
            return "WEST";

        return "UNKNOWN_DIRECTION";
    }
};
