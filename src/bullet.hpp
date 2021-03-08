#ifndef BULLET_HPP
#define BULLET_HPP

#include "common.hpp"

class Bullet
{

public:
    Bullet(/* args */) {}
    ~Bullet() {}
private:
    int bulletDamage;
    Common::Coordinates m_coordinates;
    int dir;
    bool owner; // 0 green, 1 red
    bool active;
};

#endif