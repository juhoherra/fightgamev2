#include "player.hpp"

Player::Player(Object::Ship* ship, 
               Object::Shield* shield, 
               Common::Coordinates coordinates, 
               uint16_t color, 
               Common::Players player_id, 
               Common::Ui::PointingDirection direction) :
    m_ship(ship),
    m_shield(shield),
    m_coordinates(coordinates),
    m_drawnCoordinates(coordinates),
    m_color(color),
    m_player(player_id),
    m_direction(direction)
{

}

Player::~Player()
{
    delete m_ship;
    delete m_shield;
}

Object::Ship* Player::getShip()
{
    return m_ship;
}

Object::Shield* Player::getShield()
{
    return m_shield;
}

const Common::Players Player::getID() const
{
    return m_player;
}

const Common::Ui::PointingDirection Player::getDirection() const 
{
    return m_direction;
}

const uint16_t Player::getColor() const
{
    return m_color;
}

const Common::Coordinates Player::getCoordinates() const
{
    return m_coordinates;
}

void Player::setCoordinates(Common::Coordinates coord)
{
    m_coordinates = coord;
}

const Common::Coordinates Player::returnAndUpdateUiCoordinates()
{
    Common::Coordinates temp_coord = m_drawnCoordinates;
    m_drawnCoordinates = m_coordinates;
    return temp_coord;
}