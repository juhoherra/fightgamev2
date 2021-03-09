#ifndef BULLET_HPP
#define BULLET_HPP

#include "common.hpp"

class Bullet
{

public:
    Bullet(int dmg, Common::Coordinates coords, int16_t dir, Common::Players owner, Bullet* next, Bullet* previous);
    ~Bullet();

    const int getDamage() const;
    const Common::Coordinates getCoordinates() const;
    const Common::Coordinates returnAndUpdateUiCoordinates();
    const int16_t getDirection() const;
    const Common::Players getOwner() const;
    void move();

    // Bullet* getPointerToThis() const;
    Bullet* getNextOnChain() const;
    Bullet* getPreviousOnChain() const;

    void setNextOnChain(Bullet* blt);
    void setPreviousOnChain(Bullet* blt);

private:
    int m_bulletDamage;
    Common::Coordinates m_coordinates;
    Common::Coordinates m_drawnCoordinates;
    int16_t m_dir;
    Common::Players m_owner;
    Bullet* m_referenceToPrevious;
    Bullet* m_referenceToNext;
};

#endif