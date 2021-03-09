#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include "IScreen.hpp"
#include "common.hpp"
#include "player.hpp"
#include "bullet.hpp"


namespace Ui {

typedef bool Buttons[Common::Players::PLAYER_COUNT * Common::Ui::ButtonPresses::ButtonCount];

class GameUi
{
public:
    GameUi();
    ~GameUi();

    void setupUI();

    void drawCourt();
    void drawStatistics();
    void updateAmmoStats(const int& p1Ammo, const int& p2Ammo);
    void updateHealthStats(const int& p1Health, const int& p2Health);
    void updatePlayer(Player*& player);
    void updateBullet(Bullet*& blt);
    void deleteBullet(Bullet*& blt);
    void updateRefreshRate(const uint32_t& refresrate_micros);

    void checkButtonPresses(Buttons& buttons);

    Common::GameErrors selectShip(int& health, int& damage, int& ammo, unsigned long& shootrate, unsigned long& loadrate, Common::Players player);

private:

    IScreen* m_screen;

    // Obsolete
    // Buttons m_buttonPresses; 

    const OBSOLETE::shiptype printShipSelect(const Common::Ui::Button enter, const Common::Ui::Button right, const Common::Ui::Button left) const;

};

} // namespace Ui

#endif


