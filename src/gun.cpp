#include "gun.hpp"

namespace Object {

Gun::Gun(int damage,
            int maxAmmo,
            unsigned long shootRate,
            unsigned long loadRate) :
    m_damage(damage),
    m_ammo(maxAmmo),
    m_maxAmmo(maxAmmo),
    m_shootRate(shootRate),
    m_shootTimer(0),
    m_loadRate(loadRate),
    m_loadTimer(0),
    m_loadState(LoadState::loading)
{

}

Gun::~Gun(){}

const int Gun::getDamage()
{
    return m_damage;
}

const int Gun::getAmmo()
{
    return m_ammo;
}

const int Gun::getMaxAmmo()
{
    return m_maxAmmo;
}

const unsigned long Gun::getShootRate()
{
    return m_shootRate;
}

const unsigned long Gun::getShootTimer()
{
    return m_shootTimer;
}

const unsigned long Gun::getLoadRate()
{
    return m_loadRate;
}

const unsigned long Gun::getLoadTimer()
{
    return m_loadTimer;
}

}
