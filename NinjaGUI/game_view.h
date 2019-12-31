#pragma once

#include <QMap>
#include <QPointer>
#include <QWidget>

#include "ninjasim/tile_type.h"
#include "ninjasim/simulation.h"

class GameView : public QWidget
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = nullptr);

    int tileSize() const;
    void setTileSize(int tileSize);

    void setSimulation(NinjaSim::Simulation* simulation);

signals:


protected:
    void paintEvent(QPaintEvent *event) override;

private:

    int m_tileSize;
    QPointer<NinjaSim::Simulation> m_simulation;
    QMap<NinjaSim::TileType, QPixmap> m_textures;
    QMap<char, QPixmap> m_arrows;
    QPixmap m_ninja;
};

