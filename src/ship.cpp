#include "ship.hpp"

namespace Object {

Ship::Ship(int health, Object::Gun* gun, uint32_t updateRate) :
    m_health(health),
    m_size(OBSOLETE::ShipSize), // magic number, TODO: create const/variable
    m_updateRate(updateRate),
    m_gun(gun)
{

}

Ship::~Ship() 
{
    delete m_gun;
}

Object::Gun* Ship::getGun()
{
    return m_gun;
}

const int Ship::getHealth()
{
    return m_health;
}


const uint32_t Ship::getUpdateRate()
{
    return m_updateRate;
}


const uint16_t Ship::getSize()
{
    return m_size;
}

}