#include "player.h"

#include "simulation.h"

Player::Player() :
    m_position(),
    m_direction(Direction::south()),
    m_shurikens(3),
    m_breakerMode(false),
    m_dead(false)
{
    resetDirectionPriorities();
}

void Player::setSimulation(Simulation* simulation)
{
    m_simulation = simulation;
}

QPoint Player::position() const
{
    return m_position;
}

void Player::setPosition(const QPoint& position)
{
    m_position = position;
}

QPoint Player::direction() const
{
    return m_direction;
}

void Player::setDirection(const QPoint& direction)
{
    m_direction = direction;
}

QVector<QPoint> Player::possibleDirections()
{
    QVector<QPoint> directions;

    // Add the current direction as the first item
    directions.push_back(m_direction);

    // Add the direction priorities excluding the current direction,
    // as we want to evaluate a given direction only once per turn
    for (QPoint& dir : m_directionPriorities)
    {
        if (dir != m_direction)
            directions.push_back(dir);
    }

    return directions;
}

void Player::resetDirectionPriorities()
{
    m_directionPriorities.clear();
    m_directionPriorities.push_back(Direction::south());
    m_directionPriorities.push_back(Direction::east());
    m_directionPriorities.push_back(Direction::north());
    m_directionPriorities.push_back(Direction::west());
}

void Player::reverseDirectionPriorities()
{
    QVector<QPoint> reversed;

    // Use the reverse iterator to enumerate the current direction priorities
    for (auto it = m_directionPriorities.rbegin();
         it != m_directionPriorities.rend(); ++it)
    {
        reversed.push_back(*it);
    }
    // Replace the current priorities with the reversed
    m_directionPriorities = reversed;
}

bool Player::dead() const
{
    return m_dead;
}

void Player::setDead(bool dead)
{
    m_dead = dead;
}

quint32 Player::shurikens() const
{
    return m_shurikens;
}

void Player::setShurikens(quint32 shurikens)
{
    m_shurikens = shurikens;
}

bool Player::breakerMode() const
{
    return m_breakerMode;
}

void Player::setBreakerMode(bool breakerMode)
{
    m_breakerMode = breakerMode;
}

QStringList Player::actionList() const
{
    return m_actionList;
}

QString Player::move(QPoint destination, QPoint direction)
{
    // Save the current direction
    setDirection(direction);

    // Update player position
    setPosition(destination);

    // Change properties if the player steps on a special tile
    auto tile = m_simulation->tile(destination);

    if (tile->type() == TileType::BOOSTER)
    {
        // Invert current breaker mode
        m_breakerMode = !m_breakerMode;
    }
    else if (tile->type() == TileType::SHURIKEN)
    {
        // Pick up the shuriken
        m_shurikens++;
        m_simulation->replaceTile(destination, ' ');
    }
    else if (tile->type() == TileType::ARROW)
    {
        setDirection(tile->direction());
    }
    else if (tile->type() == TileType::PATHWAY)
    {
        setPosition(tile->pathwayEndpoint());
    }

    return Direction::name(direction);
}

QString Player::runStep()
{
    QString action("NO_ACTION");

    if (!m_simulation)
        return action;

    // Move action
    // Evaluate each possible direction for this move
    for (QPoint dir : possibleDirections())
    {
        // Get the target position and the target tile
        QPoint targetPos = m_position + dir;
        auto target = m_simulation->tile(targetPos);
        // Skip non-existent tiles that would be outside the map boundaries
        if (!target) continue;

        // Change direction priorities when the player is about to step on
        // a mirror tile (which is an obstacle)
        if (target->type() == TileType::MIRROR)
        {
            reverseDirectionPriorities();
        }

        if (!target->isObstacle())
        {
            return move(targetPos, dir);
        }
        else if (m_breakerMode && target->isDestructible())
        {
            // Replace the target tile with an empty tile
            m_simulation->replaceTile(targetPos, ' ');
            return move(targetPos, dir);
        }
    }

    return action;
}
