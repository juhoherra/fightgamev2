#include "bullet.hpp"

Bullet::Bullet(int dmg, Common::Coordinates coords, int16_t dir, Common::Players owner, Bullet* next, Bullet* previous) : 
    m_bulletDamage(dmg),
    m_coordinates(coords),
    m_drawnCoordinates(coords),
    m_dir(dir),
    m_owner(owner),
    m_referenceToNext(next),
    m_referenceToPrevious(previous)
{

}
Bullet::~Bullet(){}

const int Bullet::getDamage() const
{
    return m_bulletDamage;
}

const Common::Coordinates Bullet::getCoordinates() const
{
    return m_coordinates;
}

const Common::Coordinates Bullet::returnAndUpdateUiCoordinates()
{
    Common::Coordinates temp_coord = m_drawnCoordinates;
    m_drawnCoordinates = m_coordinates;
    return temp_coord;
}

const int16_t Bullet::getDirection() const
{
    return m_dir;
}

const Common::Players Bullet::getOwner() const
{
    return m_owner;
}

void Bullet::move()
{
    m_coordinates = Common::Coordinates(m_coordinates.getXCoord() + m_dir, m_coordinates.getYCoord());
}

// Bullet* Bullet::getPointerToThis() const
// {
//     return this;
// }

Bullet* Bullet::getNextOnChain() const
{
    return m_referenceToNext;
}

Bullet* Bullet::getPreviousOnChain() const
{
    return m_referenceToPrevious;
}

void Bullet::setNextOnChain(Bullet* blt)
{
    m_referenceToNext = blt;
}

void Bullet::setPreviousOnChain(Bullet* blt)
{
    m_referenceToPrevious = blt;
}
