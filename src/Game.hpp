#ifndef GAME_HPP
#define GAME_HPP

#include "common.hpp"
#include "GameUi.hpp"
#include "player.hpp"
#include "bullet.hpp"

namespace UpdateRates {
namespace Micros {

typedef uint32_t playerRateArray[Common::Players::PLAYER_COUNT];
typedef uint32_t shootRateArray[Common::Players::PLAYER_COUNT];

typedef struct 
{
    playerRateArray player;
    shootRateArray shootrate;
    uint32_t hitMarker;
    uint32_t bullet;
    uint32_t screen;
}RefresCounter;

}
}

class Game
{

public:
    Game();
    ~Game();
    Common::GameErrors setup();
    Common::GameErrors run();

private:
    Common::GameState m_state;
    Player* m_players[Common::Players::PLAYER_COUNT];
    Ui::GameUi* m_ui;
    Bullet* m_newestBullet;

    void runShipSelector(int& health, int& damage, unsigned long& shootrate, unsigned long& loadrate);
    void updatePlayer(Player* player, const Ui::Buttons buttons);
    bool isNextCoordinateInsidePlayGround(const Common::Coordinates coord, const int16_t move_x, const int16_t move_y, const int16_t offset) const;

    uint32_t m_micros_new;
    uint32_t m_micros_old;
    uint32_t m_system_counter;

    UpdateRates::Micros::RefresCounter m_counters;


};


#endif