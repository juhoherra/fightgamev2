#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "ship.hpp"
#include "shield.hpp"
#include "common.hpp"

#include <stdint.h>


class Player
{
public:
    Player();
    Player(Object::Ship* ship, Object::Shield* shield, Common::Coordinates coordinates, uint16_t color);
    ~Player();
    Object::Ship* getShip();
    Object::Shield* getShield();
    const uint16_t getColor();
    const Common::Coordinates getCoordinates();
    void setCoordinates(Common::Coordinates coord);
    const Common::Coordinates returnAndUpdateUiCoordinates();

private:
    Object::Ship* m_ship;
    Object::Shield* m_shield;
    Common::Coordinates m_coordinates;
    Common::Coordinates m_drawnCoordinates;
    uint16_t m_color;
};
#endif