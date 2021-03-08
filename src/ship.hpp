#ifndef SHIP_HPP
#define SHIP_HPP

#include "gun.hpp"
#include "common.hpp"

namespace Object {

class Ship
{

public:
    Ship(int health, Object::Gun* gun, uint32_t updateRate = Common::UpdateRates::Micros::Constants::shipUpdateRate);
    ~Ship();

    Object::Gun* getGun();
    const int getHealth();
    const uint32_t getUpdateRate();
    const uint16_t getSize();

private:
    int m_health;
    uint16_t m_size;
    uint32_t m_updateRate;
    Object::Gun* m_gun;
};

} // namespca object

#endif