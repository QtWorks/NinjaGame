#include "game_view.h"

#include <QPainter>

#include "simulation.h"

GameView::GameView(QWidget *parent) :
    QWidget(parent),
    m_tileSize(30)
{
    setPalette(QPalette(Qt::lightGray));
    update();

    m_ninja = QPixmap(":/images/images/ninja.png");

    m_textures[TileType::BOX] = QPixmap(":/images/images/box.png");
    m_textures[TileType::WALL] = QPixmap(":/images/images/wall.png");
    m_textures[TileType::GOAL] = QPixmap(":/images/images/goal.png");
    m_textures[TileType::START] = QPixmap(":/images/images/start.png");
    m_textures[TileType::MIRROR] = QPixmap(":/images/images/mirror.png");
    m_textures[TileType::BOOSTER] = QPixmap(":/images/images/booster.png");
    m_textures[TileType::BOMB] = QPixmap(":/images/images/bomb.png");
    m_textures[TileType::PATHWAY] = QPixmap(":/images/images/pathway.png");
    m_textures[TileType::SHURIKEN] = QPixmap(":/images/images/shuriken.png");

    m_arrows['E'] = QPixmap(":/images/images/arrow-right.png");
    m_arrows['N'] = QPixmap(":/images/images/arrow-up.png");
    m_arrows['W'] = QPixmap(":/images/images/arrow-left.png");
    m_arrows['S'] = QPixmap(":/images/images/arrow-down.png");
}

void GameView::setSimulation(Simulation* simulation)
{
    m_simulation = simulation;

    if (m_simulation)
    {
        int w = m_simulation->width() * m_tileSize;
        int h = m_simulation->height() * m_tileSize;
        setFixedSize(w, h);
    }
    else
    {
        setFixedSize(300, 300);
    }
}

int GameView::tileSize() const
{
    return m_tileSize;
}

void GameView::setTileSize(int tileSize)
{
    m_tileSize = tileSize;
}

void GameView::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (!m_simulation)
        return;

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::white);

    painter.setPen(pen);

    for (int x = 0; x < m_simulation->width(); x++)
    {
        for (int y = 0; y < m_simulation->height(); y++)
        {
            auto tile = m_simulation->tile(x, y);
            if (!tile) continue;
            int px = x * m_tileSize;
            int py = y * m_tileSize;
            if (m_textures.contains(tile->type()))
            {
                auto pixmap = m_textures.value(tile->type());
                painter.drawPixmap(px, py, pixmap);
            }
            else if (tile->type() == TileType::ARROW)
            {
                auto pixmap = m_arrows.value(tile->letter());
                painter.drawPixmap(px, py, pixmap);
            }

            // Also display the letter to identify different pathways
            if (tile->type() == TileType::PATHWAY)
            {
                painter.setFont(QFont("Courier", 12, QFont::Bold));
                int cx = px + qRound(m_tileSize * 0.3f);
                int cy = py + qRound(m_tileSize * 0.7f);
                painter.drawText(cx, cy, QString(tile->letter()));
            }
        }
    }

    for (const auto& player : m_simulation->players())
    {
        if (!player->alive()) continue;
        QPoint p = player->position() * m_tileSize;
        painter.drawPixmap(p.x(), p.y(), m_ninja);
    }
}


