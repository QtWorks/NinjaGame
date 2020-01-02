#pragma once

#include <QPoint>
#include <QString>
#include <QVector>

namespace NinjaSim
{
class Direction
{
public:

    static QPoint south();
    static QPoint east();
    static QPoint north();
    static QPoint west();

    static QString name(QPoint dir);

    static QVector<QPoint> all();
};
}
