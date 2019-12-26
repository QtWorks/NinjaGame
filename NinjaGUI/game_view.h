#pragma once

#include <QMap>
#include <QPointer>
#include <QWidget>

#include "tile_type.h"
#include "simulation.h"

class GameView : public QWidget
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = nullptr);

    int tileSize() const;
    void setTileSize(int tileSize);

    void setSimulation(Simulation* simulation);

signals:


protected:
    void paintEvent(QPaintEvent *event) override;

private:

    int m_tileSize;
    QPointer<Simulation> m_simulation;
    QMap<TileType, QPixmap> m_textures;
    QMap<char, QPixmap> m_arrows;
    QPixmap m_ninja;
};

