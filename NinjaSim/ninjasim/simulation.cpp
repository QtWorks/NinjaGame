#include "simulation.h"

#include <stdexcept>

#include <QDebug>
#include <QFile>
#include <QMap>
#include <QTextStream>

#include "arrow_tile.h"
#include "bomb_tile.h"
#include "booster_tile.h"
#include "box_tile.h"
#include "empty_tile.h"
#include "goal_tile.h"
#include "mirror_tile.h"
#include "pathway_tile.h"
#include "shuriken_tile.h"
#include "start_tile.h"
#include "wall_tile.h"


namespace NinjaSim
{

Simulation::Simulation(QString filename, QObject* parent) :
    QObject(parent),
    m_completed(false),
    m_loopDetected(false),
    m_width(0),
    m_height(0)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        auto error = QString("Cannot open file: %1").arg(filename);
        throw std::runtime_error(error.toStdString());
    }

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

            QPoint current(x, y);

            auto tile = createTile(current, letter);
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
                player->setPosition(current);
                m_players.push_back(player);
            }

            if (tile->type() == TileType::PATHWAY)
            {
                // Find the other endpoint of this pathway
                if (firstEndpoints.contains(letter))
                {
                    QPoint first = firstEndpoints.value(letter);
                    auto firstEndpoint =
                        this->tile(first).staticCast<PathwayTile>();
                    // Store the respective endpoints in both tiles
                    firstEndpoint->setPathwayEndpoint(current);
                    auto secondEndpoint = tile.staticCast<PathwayTile>();
                    secondEndpoint->setPathwayEndpoint(first);
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
    y = 0;
    for (auto& line : m_tiles)
    {
        while (line.size() < m_width)
        {
            // Add some empty tiles until the line reaches full length
            TilePtr tile(new EmptyTile(' '));
            tile->setPosition(QPoint(line.size(), y));
            line.push_back(tile);
        }
        y++;
    }
}

Simulation::TilePtr Simulation::createTile(
    const QPoint& position, char letter)
{
    TilePtr tile;

    switch (letter)
    {
    case ' ':
        tile.reset(new EmptyTile(letter));
        break;
    case '@':
        tile.reset(new StartTile(letter));
        break;
    case '$':
        tile.reset(new GoalTile(letter));
        break;
    case '#':
        tile.reset(new WallTile(letter));
        break;
    case 'X':
        tile.reset(new BoxTile(letter));
        break;
    case 'M':
        tile.reset(new MirrorTile(letter));
        break;
    case 'B':
        tile.reset(new BoosterTile(letter));
        break;
    case '*':
        tile.reset(new ShurikenTile(letter));
        break;
    case 'S':
    case 'E':
    case 'N':
    case 'W':
        tile.reset(new ArrowTile(letter));
        break;
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
        tile.reset(new PathwayTile(letter));
        break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        tile.reset(new BombTile(letter));
        break;
    default:
        qDebug("Unhandled letter: '%c' (code: %d)", letter, (int)letter);
        return nullptr;
    }

    tile->setPosition(position);

    // Add this tile to the dynamic tiles
    if (tile->isDynamic())
    {
        m_dynamicTiles.push_back(tile);
    }

    return tile;
}

Simulation::TilePtr Simulation::replaceTile(
    const QPoint& position, char letter)
{
    auto current = tile(position);
    // We cannot replace a non-existent tile
    if (!current)
        return nullptr;

    // If we are replacing the GOAL tile, then the game should be finished
    if (current->type() == TileType::GOAL)
        m_completed = true;

    // Create and store the new tile
    auto newTile = createTile(position, letter);
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

bool Simulation::completed() const
{
    return m_completed;
}

bool Simulation::loopDetected() const
{
    return m_loopDetected;
}

bool Simulation::canProceed() const
{
    if (m_completed || m_loopDetected)
        return false;

    return true;
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

QVector<Simulation::PlayerPtr> Simulation::findPlayers(
    const QPoint& position) const
{
    QVector<PlayerPtr> result;

    for (auto player : m_players)
    {
        if (player->position() == position)
            result.push_back(player);
    }

    return result;
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

Simulation::TilePtr Simulation::findDestructibleTile(
    const QPoint& position, const QPoint& direction, bool goalOnly) const
{
    int maxSteps = qMax(m_width, m_height);

    QPoint targetPos = position;

    for (int i = 0; i < maxSteps; i++)
    {
        // Move by one step in the given direction
        targetPos += direction;

        auto target = tile(targetPos);
        // Return right away if we step outside the map boundaries
        if (!target)
            return nullptr;

        // Abort further search if we step on an indestructible obstacle
        if (target->isObstacle() && !target->isDestructible())
            return nullptr;

        // Check if this tile is destructible
        if (target->isDestructible())
        {
            if (goalOnly)
            {
                // If goalOnly is true, check if this is a GOAL tile
                if (target->type() == TileType::GOAL)
                    return target;
            }
            else
            {
                // Otherwise return this destructible tile
                return target;
            }

        }
    }

    return nullptr;
}

void Simulation::activateBombsAround(const QPoint& position)
{
    // Try all 4 directions
    for (QPoint dir : Direction::all())
    {
        // Add the current direction to the starting position
        QPoint targetPos = position + dir;

        auto target = tile(targetPos);
        // Skip non-existent tiles that would be outside the map boundaries
        if (!target) continue;

        // Activate any bomb tiles
        if (target->type() == TileType::BOMB)
        {
            target.staticCast<BombTile>()->setActivated(true);
        }
    }
}

QString Simulation::toString() const
{
    QString result;
    QTextStream out(&result);

    // Print all map tiles to the result
    out << "Map:" << endl;

    for (int x = 0; x < m_width; x++)
    {
        for (int y = 0; y < m_height; y++)
        {
            out << tile(x, y)->letter();
        }
        out << endl;
    }

    // Print all player data to the result
    out << "Players:" << endl;
    for (auto& player : m_players)
    {
        if (player->dead()) continue;
        out << *player << endl;
    }

    return result;
}

QString Simulation::runSingleStep()
{
    QString action;

    if (!canProceed())
        return action;

    // Run a single step for each dynamic tile
    for (auto tile : m_dynamicTiles)
    {
        tile->runStep(this);
    }

    // Run a single action for each player
    for (auto player : m_players)
    {
        if (player->dead()) continue;
        action = player->runStep();
    }

    // If the primary player is dead, then the game should be completed
    if (m_players[0]->dead())
        m_completed = true;

    // If the game is finished, we add a "GAME OVER" action to the action list
    // of the primary player
    if (m_completed)
    {
        m_players[0]->addAction("GAME OVER");
    }

    // Get the current state as a string
    QString state = toString();
    // Check if the simulation was in the exact same state before
    if (m_previousStates.contains(state))
    {
        // We have identified a loop!
        m_loopDetected = true;
    }
    else
    {
        // Save the current state
        m_previousStates[state] = 1;
    }

    return action;
}

bool Simulation::runFullGame()
{
    const int maxSteps = 1000;

    if (!canProceed())
        return m_completed;

    for (int i = 0; i < maxSteps; i++)
    {
        runSingleStep();
        if (m_completed || m_loopDetected)
            break;
    }

    return m_completed;
}

}

