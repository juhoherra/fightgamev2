#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "ship.hpp"
#include "shield.hpp"
#include "common.hpp"

#include <stdint.h>


class Player
{
public:
    Player(Object::Ship* ship, 
           Object::Shield* shield, 
           Common::Coordinates coordinates, 
           uint16_t color, 
           Common::Players player_id,
           Common::Ui::PointingDirection direction);
    ~Player();
    Object::Ship* getShip();
    Object::Shield* getShield();
    const Common::Players getID() const;
    const Common::Ui::PointingDirection getDirection() const;
    const uint16_t getColor() const;
    const Common::Coordinates getCoordinates() const;
    void setCoordinates(Common::Coordinates coord);
    const Common::Coordinates returnAndUpdateUiCoordinates();

private:
    Object::Ship* m_ship;
    Object::Shield* m_shield;
    Common::Coordinates m_coordinates;
    Common::Coordinates m_drawnCoordinates;
    uint16_t m_color;
    Common::Players m_player;
    Common::Ui::PointingDirection m_direction;

};
#endif