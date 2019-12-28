#pragma once

#include <QHash>
#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QStringList>
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

    TilePtr tile(const QPoint& position) const;
    TilePtr tile(int x, int y) const;
    TilePtr replaceTile(const QPoint& position, char letter);

    TilePtr findDestructibleTile(
        const QPoint& position, const QPoint& direction, bool goalOnly) const;

    int width() const;
    int height() const;

    bool finished() const;
    bool loopDetected() const;

    const QVector<PlayerPtr> players() const;
    PlayerPtr primaryPlayer() const;

    QString toString() const;

    QString runSingleStep();

    bool runFullGame();

signals:

private:

    TilePtr createTile(char letter) const;

private:

    bool m_finished;
    bool m_loopDetected;

    QVector<PlayerPtr> m_players;

    int m_width;
    int m_height;
    QVector<QVector<TilePtr>> m_tiles;

    QHash<QString, int> m_previousStates;
};
