#include "Game.hpp"
#include "common.hpp"

#include "Arduino.h"

Game::Game() : 
    m_state(Common::GameState::GameStopped),
    m_ui(new Ui::GameUi()),
    m_micros_new(0x0),
    m_micros_old(0x0),
    m_system_counter(0x0)
{
    m_newestBullet = nullptr;
}

Game::~Game()
{
}

Common::GameErrors Game::setup()
{
    m_state = Common::GameState::GameInSetup;
    Common::GameErrors error_code = Common::GameErrors::UnknownError;

    // Todo Check if checking of return value is valuable
    m_ui->setupUI();

    pinMode(Common::Ui::Button::PLAYER_1_BUTTON_LEFT, INPUT);
    pinMode(Common::Ui::Button::PLAYER_1_BUTTON_RIGHT, INPUT);
    pinMode(Common::Ui::Button::PLAYER_2_BUTTON_LEFT, INPUT);
    pinMode(Common::Ui::Button::PLAYER_2_BUTTON_RIGHT, INPUT);
    pinMode(Common::Ui::Button::PLAYER_1_BUTTON_SHOOT, INPUT);
    pinMode(Common::Ui::Button::PLAYER_2_BUTTON_SHOOT, INPUT);
    pinMode(Common::Ui::Button::ENTER_BUTTON, INPUT);

    int health {0};
    int damage {0};
    int ammo {0};
    unsigned long shootrate {0};
    unsigned long loadrate {0};    

    Common::Coordinates coord[Common::Players::PLAYER_COUNT] =
        {Common::Coordinates(Common::Ui::PLAYER_1_X, Common::Ui::PLAYER_1_Y),
         Common::Coordinates(Common::Ui::PLAYER_2_X, Common::Ui::PLAYER_2_Y)};

    for (int i = Common::Players::Player1; i < Common::Players::PLAYER_COUNT; i++)
    {
        error_code = m_ui->selectShip(health, damage, ammo, shootrate, loadrate, (Common::Players)i);
        if (error_code)
        {
            return error_code;
        }

        m_players[(Common::Players)i] = new Player(new Object::Ship(health, new Object::Gun(damage, ammo, shootrate, loadrate)),
                                                    new Object::Shield(false, 200),
                                                    coord[i],
                                                    Common::Ui::PlayerColors[(Common::Players)i],
                                                    (Common::Players)i,
                                                    (Common::Ui::Direction[i])
                                                    );
        
        delay(500);
    }
    
    delay(500);

    m_ui->drawStatistics();
    m_ui->drawCourt();
    m_ui->updateAmmoStats(m_players[Common::Players::Player1]->getShip()->getGun()->getAmmo(),
                          m_players[Common::Players::Player2]->getShip()->getGun()->getAmmo());
    m_ui->updateHealthStats(m_players[Common::Players::Player1]->getShip()->getHealth(),
                            m_players[Common::Players::Player2]->getShip()->getHealth());

    m_counters.player[Common::Players::Player1] = 0;
    m_counters.player[Common::Players::Player2] = 0;
    m_counters.bullet = 0;
    m_counters.screen = 0;
    m_counters.hitMarker = 0;

    return Common::GameErrors::NoError;
                            
}

Common::GameErrors Game::run()
{
    // overcome delay in setup
    m_micros_new = micros();
    while(true)
    {
        m_micros_old = m_micros_new;
        m_micros_new = micros();
        uint32_t loop_time = 0x0;
        if (m_micros_new < m_micros_old) 
        {
            loop_time = 0xffffffff - m_micros_old + m_micros_new;
        }
        else 
        {
            loop_time = m_micros_new - m_micros_old;
        }

        m_counters.player[Common::Players::Player1] += loop_time;
        m_counters.player[Common::Players::Player2] += loop_time;
        m_counters.shootrate[Common::Players::Player1] += loop_time;
        m_counters.shootrate[Common::Players::Player2] += loop_time;
        m_counters.bullet += loop_time;
        m_counters.screen += loop_time;
        m_counters.hitMarker += loop_time;

        Ui::Buttons buttons {0}; 

        m_ui->checkButtonPresses(buttons);

        // update players
        for (int i = Common::Players::Player1; i < Common::Players::PLAYER_COUNT; i++)
        {
            if (m_counters.player[i] > m_players[i]->getShip()->getUpdateRate())
            {
                //do player things
                int startIndex = i * (int)Common::Ui::ButtonPresses::ButtonCount;
                updatePlayer(m_players[i], &buttons[startIndex]);

                m_counters.player[i] = 0x0;
            }
            
            
        }

        if (m_counters.bullet > Common::UpdateRates::Micros::Constants::bulletUpdateRate)
        {
            Bullet* blt = m_newestBullet;
            Bullet* nextBullet = nullptr;
            while (blt != nullptr)
            {
                if (isNextCoordinateInsidePlayGround(blt->getCoordinates(), blt->getDirection(), 0, -blt->getDirection()))
                {
                    blt->move();
                    if(blt->getNextOnChain() != nullptr)
                    {  
                        nextBullet = blt->getNextOnChain();
                    }
                    else
                    {
                        nextBullet = nullptr;
                    }
                }
                else
                {
                    // deleting bullet
                    if (blt->getNextOnChain() == nullptr && blt->getPreviousOnChain() == nullptr)
                    {
                        m_newestBullet = nullptr;
                        nextBullet = nullptr;
                    }
                    else if (blt->getNextOnChain() == nullptr)
                    {
                        blt->getPreviousOnChain()->setNextOnChain(nullptr);
                        nextBullet = nullptr;
                    }
                    else if (blt->getPreviousOnChain() == nullptr)
                    {
                        blt->getNextOnChain()->setPreviousOnChain(nullptr);
                        nextBullet = blt->getNextOnChain();
                        m_newestBullet = nullptr;
                    }
                    else 
                    {
                        blt->getNextOnChain()->setPreviousOnChain(blt->getPreviousOnChain());
                        blt->getPreviousOnChain()->setNextOnChain(blt->getNextOnChain());
                        nextBullet = blt->getNextOnChain();
                    }
                    m_ui->deleteBullet(blt);
                    delete blt;
                }
                blt = nextBullet;
            }

            m_counters.bullet = 0x0;
        }

        if (m_counters.screen > Common::UpdateRates::Micros::Constants::screenUpdateRate)
        {
            // update stuff
            // update players
            // update bullets etc...
            uint32_t temp_updaterate = m_counters.screen;
            
            m_counters.screen = 0x0;
            
            for (Player* player : m_players)
            {
                m_ui->updatePlayer(player);
            }
            
            Bullet* blt = m_newestBullet;
            while (blt != nullptr)
            {
                m_ui->updateBullet(blt);
                blt = blt->getNextOnChain();
            }

            m_ui->updateRefreshRate(temp_updaterate);

        }
    }
}


void Game::updatePlayer(Player* player, const Ui::Buttons buttons)
{
    // movement
    bool moved = (buttons[Common::Ui::ButtonPresses::Right] && buttons[Common::Ui::ButtonPresses::Left] || 
                  !buttons[Common::Ui::ButtonPresses::Right] && !buttons[Common::Ui::ButtonPresses::Left])
                  ? false : true;
    if (moved)
    {
        int16_t move_y = (buttons[Common::Ui::ButtonPresses::Right]) ? -1 : 1;
        if (isNextCoordinateInsidePlayGround(player->getCoordinates(), 0, move_y, OBSOLETE::HalfShipSize))
        {
            player->setCoordinates(Common::Coordinates(player->getCoordinates().getXCoord(),
                                                      (uint16_t)(player->getCoordinates().getYCoord() + move_y)));
        }
    }
    
    // shoot
    if (buttons[Common::Ui::ButtonPresses::Shoot] && 
        player->getShip()->getGun()->getAmmo() > 0 &&
        m_counters.shootrate[player->getID()] > player->getShip()->getGun()->getShootRate())
    {
        Common::Coordinates blt_coord(player->getCoordinates().getXCoord() + player->getDirection() * (OBSOLETE::gunSize + 2),
                                      player->getCoordinates().getYCoord());
        Bullet* bullet = new Bullet(player->getShip()->getGun()->getDamage(),
                                    blt_coord,
                                    player->getDirection(),
                                    player->getID(),
                                    m_newestBullet,
                                    nullptr);
        
        if (m_newestBullet != nullptr)
        {
            m_newestBullet->setPreviousOnChain(bullet);
        }
        m_newestBullet = bullet;
        m_counters.shootrate[player->getID()] = 0x0;


        // player ammo down
        // player shoot timer zero

    }
}

bool Game::isNextCoordinateInsidePlayGround(const Common::Coordinates coord, const int16_t move_x, const int16_t move_y, const int16_t offset) const
{
    return (coord.getXCoord() + move_x > Common::Ui::courtSizeXmin + offset) &&
                (coord.getXCoord() + move_x < Common::Ui::courtSizeXmax - offset) &&
                (coord.getYCoord() + move_y > Common::Ui::courtSizeYmin + offset) &&
                (coord.getYCoord() + move_y < Common::Ui::courtSizeYmax + offset);
}

