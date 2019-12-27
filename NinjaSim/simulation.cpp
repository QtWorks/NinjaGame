#include "simulation.h"

#include <stdexcept>

#include <QFile>
#include <QMap>

Simulation::Simulation(QObject *parent) :
    QObject(parent),
    m_finished(false),
    m_width(0),
    m_height(0)
{
}

void Simulation::loadMapFromFile(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        auto error = QString("Cannot open file: %1").arg(filename);
        throw std::runtime_error(error.toStdString());
    }

    m_finished = false;
    m_width = 0;
    m_height = 0;
    m_tiles.clear();
    m_players.clear();

    // Helper map to store the first endpoint of each pathway pair
    QMap<char, QPoint> firstEndpoints;

    int y = 0;
    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        // Skip empty lines
        if (line.size() == 0)
            continue;

        // Allocate space for next line
        m_tiles.resize(y + 1);
        m_height = m_tiles.size();

        for (int x = 0; x < line.size(); x++)
        {
            char letter = line[x];
            // Break at EOL characters
            if (letter == '\n' || letter == '\r')
                break;

            auto tile = createTile(letter);
            if (tile.isNull())
            {
                QString error("Invalid character in line %1: '%2'");
                error = error.arg(y).arg(letter);
                throw std::runtime_error(error.toStdString());
            }

            if (tile->type() == TileType::START)
            {
                // Create a new player for each start tile
                PlayerPtr player(new Player());
                player->setSimulation(this);
                player->setPosition(QPoint(x, y));
                m_players.push_back(player);
            }

            if (tile->type() == TileType::PATHWAY)
            {
                QPoint current(x, y);
                // Find the other endpoint of this pathway
                if (firstEndpoints.contains(letter))
                {
                    QPoint first = firstEndpoints.value(letter);
                    TilePtr firstTile = this->tile(first.x(), first.y());
                    // Store the respective endpoints in both tiles
                    firstTile->setPathwayEndpoint(current);
                    tile->setPathwayEndpoint(first);
                }
                else
                {
                    // Store the current endpoint in firstEndpoints
                    firstEndpoints.insert(letter, current);
                }
            }

            m_tiles[y].push_back(tile);

            if (m_tiles[y].size() > m_width)
                m_width = m_tiles[y].size();
        }

        y++;
    }

    if (m_height == 0 || m_width == 0)
    {
        throw std::runtime_error("Invalid map: No lines found.");
    }

    if (m_players.empty())
    {
        throw std::runtime_error("Invalid map: No start positions found.");
    }

    // At this point, the map width is known, so we need to make sure that
    // each line has the same number of tiles to enforce a rectangular layout
    for (auto& line : m_tiles)
    {
        while (line.size() < m_width)
        {
            // Add some empty tiles until the line reaches full length
            TilePtr tile(new Tile(TileType::EMPTY, ' '));
            line.push_back(tile);
        }
    }

}

Simulation::TilePtr Simulation::createTile(char letter) const
{
    TilePtr tile;

    switch (letter)
    {
    case ' ':
        tile.reset(new Tile(TileType::EMPTY, letter));
        break;
    case '@':
        tile.reset(new Tile(TileType::START, letter));
        break;
    case '$':
        tile.reset(new Tile(TileType::GOAL, letter));
        break;
    case '#':
        tile.reset(new Tile(TileType::WALL, letter));
        break;
    case 'X':
        tile.reset(new Tile(TileType::BOX, letter));
        break;
    case 'M':
        tile.reset(new Tile(TileType::MIRROR, letter));
        break;
    case 'B':
        tile.reset(new Tile(TileType::BOOSTER, letter));
        break;
    case '*':
        tile.reset(new Tile(TileType::SHURIKEN, letter));
        break;
    case 'S':
    case 'E':
    case 'N':
    case 'W':
        tile.reset(new Tile(TileType::ARROW, letter));
        break;
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
        tile.reset(new Tile(TileType::PATHWAY, letter));
        break;
    default:
        qDebug("Unhandled letter: '%c' (code: %d)", letter, (int)letter);
        break;
    }

    return tile;
}

bool Simulation::finished() const
{
    return m_finished;
}

void Simulation::setFinished(bool finished)
{
    m_finished = finished;
}

const QVector<Simulation::PlayerPtr> Simulation::players() const
{
    return m_players;
}

Simulation::PlayerPtr Simulation::primaryPlayer() const
{
    if (m_players.size() > 0)
        return m_players[0];

    return nullptr;
}

Simulation::TilePtr Simulation::tile(const QPoint& position) const
{
    return tile(position.x(), position.y());
}

Simulation::TilePtr Simulation::tile(int x, int y) const
{
    if (y >=0 && y < m_tiles.size())
    {
        auto line = m_tiles.at(y);
        if (x >=0 && x < line.size())
             return line.at(x);
    }

    return nullptr;
}

Simulation::TilePtr Simulation::replaceTile(const QPoint& position, char letter)
{
    auto current = tile(position);
    // We cannot replace a non-existent tile
    if (!current)
        return nullptr;

    auto newTile = createTile(letter);
    m_tiles[position.y()][position.x()] = newTile;
    return newTile;
}

int Simulation::width() const
{
    return m_width;
}

int Simulation::height() const
{
    return m_height;
}

QString Simulation::runSingleStep()
{
    QString action;

    if (m_finished || m_players.empty())
        return action;

    for (auto player : m_players)
    {
        action = player->runStep();
    }

    return action;
}

bool Simulation::runFullGame()
{
    return false;
}


