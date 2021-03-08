#include "player.hpp"

Player::Player(){}

Player::Player(Object::Ship* ship, Object::Shield* shield, Common::Coordinates coordinates, uint16_t color) :
    m_ship(ship),
    m_shield(shield),
    m_coordinates(coordinates),
    m_drawnCoordinates(coordinates),
    m_color(color)
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

const uint16_t Player::getColor()
{
    return m_color;
}


const Common::Coordinates Player::getCoordinates()
{
    return m_coordinates;
}

void Player::setCoordinates(Common::Coordinates coord)
{
    m_coordinates.x_coord = coord.x_coord;
    m_coordinates.y_coord = coord.y_coord;
}

const Common::Coordinates Player::returnAndUpdateUiCoordinates()
{
    Common::Coordinates temp_coord = m_drawnCoordinates;
    m_drawnCoordinates = m_coordinates;
    return temp_coord;
}