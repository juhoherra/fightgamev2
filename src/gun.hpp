#ifndef GUN_HPP
#define GUN_HPP

enum LoadState
{
    loading,
    notLoading
};

namespace Object 
{

class Gun
{

public:
    Gun(int damage,
        int maxAmmo,
        unsigned long shootRate,
        unsigned long loadRate);
    ~Gun();

    const int getDamage();
    const int getAmmo();
    const int getMaxAmmo();

    const unsigned long getShootRate();
    const unsigned long getShootTimer();
    const unsigned long getLoadRate();
    const unsigned long getLoadTimer();

private:
    int m_damage;
    int m_ammo;
    int m_maxAmmo;
    unsigned long m_shootRate;
    unsigned long m_shootTimer;
    unsigned long m_loadRate;
    unsigned long m_loadTimer;
    LoadState m_loadState;
};

}


#endif