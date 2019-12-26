#include "player.h"

Player::Player() :
    m_position(),
    m_direction(),
    m_shurikens(3),
    m_breakerMode(false),
    m_alive(true)
{
    resetDirectionPriorities();
}

QPoint Player::position() const
{
    return m_position;
}

void Player::setPosition(const QPoint &position)
{
    m_position = position;
}

QPoint Player::direction() const
{
    return m_direction;
}

void Player::setDirection(const QPoint &direction)
{
    m_direction = direction;
}

QPoint Player::followNextDirection()
{
    int current = m_directionPriorities.indexOf(m_direction);
    int next = (current + 1) % m_directionPriorities.size();
    m_direction = m_directionPriorities[next];

    return m_direction;
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

bool Player::alive() const
{
    return m_alive;
}

void Player::setAlive(bool alive)
{
    m_alive = alive;
}

quint32 Player::shurikens() const
{
    return m_shurikens;
}

void Player::setShurikens(const quint32 &shurikens)
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
