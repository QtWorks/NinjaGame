#include "direction.h"

namespace NinjaSim
{

QPoint Direction::south()
{
    return QPoint(0, 1);
}

QPoint Direction::east()
{
    return QPoint(1, 0);
}

QPoint Direction::north()
{
    return QPoint(0, -1);
}

QPoint Direction::west()
{
    return QPoint(-1, 0);
}

QString Direction::name(QPoint dir)
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

QVector<QPoint> Direction::all()
{
    QVector<QPoint> result;

    result.push_back(south());
    result.push_back(east());
    result.push_back(north());
    result.push_back(west());

    return result;
}

}
