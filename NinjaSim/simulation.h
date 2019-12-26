#pragma once

#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QVector>

#include "tile.h"
#include "player.h"

class Simulation : public QObject
{
public:

    using TilePtr = QSharedPointer<Tile>;
    using PlayerPtr = QSharedPointer<Player>;

public:

    explicit Simulation(QObject *parent = nullptr);

    void loadMapFromFile(QString filename);

    TilePtr tile(int x, int y) const;

    int width() const;

    int height() const;

    const QVector<PlayerPtr> players() const;

signals:

private:

    TilePtr createTile(char letter) const;


private:

    QVector<PlayerPtr> m_players;

    int m_width;
    int m_height;
    QVector<QVector<TilePtr>> m_tiles;

};
