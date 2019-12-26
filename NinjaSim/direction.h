#pragma once

#include <QPoint>

class Direction
{
public:

    static QPoint south() { return QPoint(0,1); }
    static QPoint east() { return QPoint(1,0); }
    static QPoint north() { return QPoint(0,-1); }
    static QPoint west() { return QPoint(-1,0); }
};
