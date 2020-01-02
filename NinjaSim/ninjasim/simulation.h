#pragma once

#include <QHash>
#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QStringList>
#include <QVector>

#include "tile.h"
#include "bomb_tile.h"
#include "player.h"

namespace NinjaSim
{
class Simulation : public QObject
{
public:

    using TilePtr = QSharedPointer<Tile>;
    using PlayerPtr = QSharedPointer<Player>;

public:

    explicit Simulation(QString filename, QObject* parent = nullptr);

    TilePtr tile(const QPoint& position) const;
    TilePtr tile(int x, int y) const;

    TilePtr findDestructibleTile(
        const QPoint& position, const QPoint& direction, bool goalOnly) const;

    void activateBombsAround(const QPoint& position);

    int width() const;
    int height() const;

    bool completed() const;
    bool loopDetected() const;

    bool canProceed() const;

    const QVector<PlayerPtr> players() const;
    PlayerPtr primaryPlayer() const;

    QString toString() const;

    QString runSingleStep();

    bool runFullGame();

signals:

private:

    TilePtr createTile(const QPoint& position, char letter);
    TilePtr replaceTile(const QPoint& position, char letter);

private:

    friend class Player;
    friend class BombTile;

    bool m_completed;
    bool m_loopDetected;

    QVector<PlayerPtr> m_players;

    int m_width;
    int m_height;
    QVector<QVector<TilePtr>> m_tiles;
    QVector<TilePtr> m_dynamicTiles;

    QHash<QString, int> m_previousStates;
};
}
