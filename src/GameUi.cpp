#include "GameUi.hpp"
#include "AdafruitTFTDriver.hpp"

namespace Ui {

GameUi::GameUi() :
    m_screen(new Adafruit::AdafruitTFTDriver())
{
    // for (bool* buttonpress : m_buttonPresses)
    // {
    //     buttonpress = false;
    // }
}

GameUi::~GameUi()
{
    delete m_screen;
}

void GameUi::drawCourt() 
{
    m_screen->drawRect(Common::Ui::courtSizeXmin,
                       Common::Ui::courtSizeYmin,
                       Common::Ui::courtSizeXmax -50,
                       Common::Ui::courtSizeYmax -40,
                       Common::Ui::WHITE);
}

void GameUi::drawStatistics()
{
    const char health[] = "HEALTH: ";
    m_screen->setCursor(55,30);
    m_screen->setTextColor(Common::Ui::WHITE);
    m_screen->setTextSize(1);
    m_screen->print(health, sizeof(health));
    
    m_screen->setCursor(360,30);
    m_screen->setTextColor(Common::Ui::WHITE);
    m_screen->setTextSize(1);
    m_screen->print(health, sizeof(health));
    
    const char ammo[] = "AMMO: ";
    m_screen->setCursor(55,285);
    m_screen->setTextColor(Common::Ui::WHITE);
    m_screen->setTextSize(1);
    m_screen->print(ammo, sizeof(ammo));
    
    m_screen->setCursor(380,285);
    m_screen->setTextColor(Common::Ui::WHITE);
    m_screen->setTextSize(1);
    m_screen->print(ammo, sizeof(ammo));
}

void GameUi::updateHealthStats(const int& p1Health, const int& p2Health) {
    
    m_screen->fillRect(Common::Ui::ConstantCoordinates::Player1HealthX,
                       Common::Ui::ConstantCoordinates::Player1HealthY,
                       Common::Ui::ConstantCoordinates::statrectsizeX,
                       Common::Ui::ConstantCoordinates::statrectsizeY,
                       Common::Ui::BLACK);
    m_screen->setCursor(Common::Ui::ConstantCoordinates::Player1HealthX,
                        Common::Ui::ConstantCoordinates::Player1HealthY);
    m_screen->print(p1Health);

    m_screen->fillRect(Common::Ui::ConstantCoordinates::Player2HealthX,
                       Common::Ui::ConstantCoordinates::Player2HealthY,
                       Common::Ui::ConstantCoordinates::statrectsizeX,
                       Common::Ui::ConstantCoordinates::statrectsizeY,
                       Common::Ui::BLACK);
    m_screen->setCursor(Common::Ui::ConstantCoordinates::Player2HealthX,
                        Common::Ui::ConstantCoordinates::Player2HealthY);
    m_screen->print(p2Health);
}

void GameUi::updateAmmoStats(const int& p1Ammo, const int& p2Ammo) {

    m_screen->fillRect(Common::Ui::ConstantCoordinates::Player1AmmoX,
                       Common::Ui::ConstantCoordinates::Player1AmmoY,
                       Common::Ui::ConstantCoordinates::statrectsizeX,
                       Common::Ui::ConstantCoordinates::statrectsizeY,
                       Common::Ui::BLACK);
    m_screen->setCursor(Common::Ui::ConstantCoordinates::Player1AmmoX,
                        Common::Ui::ConstantCoordinates::Player1AmmoY);
    m_screen->print(p1Ammo);

    m_screen->fillRect(Common::Ui::ConstantCoordinates::Player2AmmoX,
                       Common::Ui::ConstantCoordinates::Player2AmmoY,
                       Common::Ui::ConstantCoordinates::statrectsizeX,
                       Common::Ui::ConstantCoordinates::statrectsizeY,
                       Common::Ui::BLACK);
    m_screen->setCursor(Common::Ui::ConstantCoordinates::Player2AmmoX,
                        Common::Ui::ConstantCoordinates::Player2AmmoY);
    m_screen->print(p2Ammo);
}


void GameUi::setupUI()
{
    m_screen->reset();
    const uint16_t identifier = m_screen->readID();
    m_screen->begin(identifier);
    m_screen->setRotation(3);
    m_screen->fillScreen(Common::Ui::BLACK);
}

void GameUi::updatePlayer(Player*& player)
{
    // This only removes and draws the changed part
    Common::Coordinates lastpos = player->returnAndUpdateUiCoordinates();
    int16_t diff = player->getCoordinates().y_coord - lastpos.y_coord;
    if (lastpos = player->getCoordinates) return;
    if(diff > 0)
    {
        m_screen->drawVLine(lastpos.x_coord, 
                            lastpos.y_coord,
                            diff,
                            Common::Ui::Color::BLACK);
        m_screen->drawVLine(lastpos.x_coord + 1,
                            lastpos.y_coord,
                            diff,
                            Common::Ui::Color::BLACK);
        m_screen->drawVLine(lastpos.x_coord, 
                            lastpos.y_coord + player->getShip()->getSize(),
                            diff,
                            player->getColor());
        m_screen->drawVLine(lastpos.x_coord + 1, 
                            lastpos.y_coord + player->getShip()->getSize(),
                            diff,
                            player->getColor());
    }
    else if (diff < 0)
    {
        m_screen->drawVLine(player->getCoordinates().x_coord,
                            player->getCoordinates().y_coord + player->getShip()->getSize(),
                            -diff,
                            Common::Ui::Color::BLACK);
        m_screen->drawVLine(player->getCoordinates().x_coord + 1,
                            player->getCoordinates().y_coord + player->getShip()->getSize(),
                            -diff,
                            Common::Ui::Color::BLACK);
        m_screen->drawVLine(player->getCoordinates().x_coord, 
                            player->getCoordinates().y_coord,
                            -diff,
                            player->getColor());
        m_screen->drawVLine(player->getCoordinates().x_coord + 1, 
                            player->getCoordinates().y_coord,
                            -diff,
                            player->getColor());
    }
    //draw gun
    m_screen->drawHLine(lastpos.x_coord - (2 /*+ direction*/) * 8,
                        lastpos.y_coord + player->getShip()->getSize() / 2 + 1,
                        16, // gun size
                        Common::Ui::Color::BLACK);
    m_screen->drawHLine(player->getCoordinates().x_coord - (2 /*+ direction*/) * 8,
                        player->getCoordinates().y_coord + player->getShip()->getSize() / 2 + 1,
                        16, // gun size
                        player->getColor());


    // tft.drawFastVLine(playerToDraw.xCoor,       playerToDraw.yCoor, playerToDraw.shipSize, color);
    // tft.drawFastVLine(playerToDraw.xCoor + dir, playerToDraw.yCoor, playerToDraw.shipSize, color);
    // tft.drawFastHLine(playerToDraw.xCoor - (1+dir)*8, playerToDraw.yCoor + playerToDraw.shipSize / 2 +1, 16, color);
    // if (playerToDraw.shield) {
    //     tft.drawFastVLine(playerToDraw.xCoor - dir*8, playerToDraw.yCoor, playerToDraw.shipSize, color);
    // }
}

void GameUi::updateRefreshRate(const uint32_t& refresrate_micros)
{
    m_screen->fillRect(10, 10, 100, 20, Common::Ui::BLACK);
    m_screen->setCursor(10, 10);
    const char text[] = "ms";
    const uint32_t millisecs = refresrate_micros / 1000;
    m_screen->print(millisecs);
    m_screen->setCursor(30, 10);
    m_screen->print(text, sizeof(text));
}

void GameUi::checkButtonPresses(Buttons& buttons)
{
    buttons[Common::Players::Player1 * Common::Ui::ButtonPresses::ButtonCount + Common::Ui::ButtonPresses::Right]
        = digitalRead(Common::Ui::PLAYER_1_BUTTON_RIGHT);
    
    buttons[Common::Players::Player1 * Common::Ui::ButtonPresses::ButtonCount + Common::Ui::ButtonPresses::Left]
        = digitalRead(Common::Ui::PLAYER_1_BUTTON_LEFT);

    buttons[Common::Players::Player1 * Common::Ui::ButtonPresses::ButtonCount + Common::Ui::ButtonPresses::Shoot]
        = digitalRead(Common::Ui::PLAYER_1_BUTTON_SHOOT);
    
    buttons[Common::Players::Player2 * Common::Ui::ButtonPresses::ButtonCount + Common::Ui::ButtonPresses::Right]
        = digitalRead(Common::Ui::PLAYER_2_BUTTON_RIGHT);

    buttons[Common::Players::Player2 * Common::Ui::ButtonPresses::ButtonCount + Common::Ui::ButtonPresses::Left]
        = digitalRead(Common::Ui::PLAYER_2_BUTTON_LEFT);
    
    buttons[Common::Players::Player2 * Common::Ui::ButtonPresses::ButtonCount + Common::Ui::ButtonPresses::Shoot]
        = digitalRead(Common::Ui::PLAYER_2_BUTTON_SHOOT);   

}

Common::GameErrors GameUi::selectShip(int& health, int& damage, int& ammo, unsigned long& shootrate, unsigned long& loadrate, Common::Players player)
{
    m_screen->fillScreen(Common::Ui::BLACK);
    m_screen->setCursor(30,10);
    m_screen->setTextColor(Common::Ui::WHITE);
    m_screen->setTextSize(3);
    
    const char text[] = "CHOOSE YOUR SHIP!";
    m_screen->print(text, sizeof(text));

    OBSOLETE::shiptype ship;

    if (player == Common::Players::Player1)
    {
        ship = printShipSelect(Common::Ui::Button::PLAYER_1_BUTTON_SHOOT, 
                                    Common::Ui::Button::PLAYER_1_BUTTON_LEFT,
                                    Common::Ui::Button::PLAYER_1_BUTTON_RIGHT);
    }
    else if (player == Common::Players::Player2)
    {
        ship = printShipSelect(Common::Ui::Button::PLAYER_2_BUTTON_SHOOT, 
                                    Common::Ui::Button::PLAYER_2_BUTTON_LEFT,
                                    Common::Ui::Button::PLAYER_2_BUTTON_RIGHT);
    }
    else
    {
        return Common::GameErrors::SetupError;
    }

//    if (*ship == *OBSOLETE::errortype)
//    {
//        return Common::GameErrors::SetupError;
//    }

    m_screen->fillScreen(Common::Ui::BLACK);
    
    health = ship.health;
    damage = ship.damage;
    ammo = ship.ammo;
    shootrate = ship.shootrate;
    loadrate = ship.loadrate;

    return Common::GameErrors::NoError;
}

const OBSOLETE::shiptype GameUi::printShipSelect(const Common::Ui::Button enter, const Common::Ui::Button right, const Common::Ui::Button left) const
{
    const char fast_str[] = "FAST";
    const char med_str[] = "MEDIUM";
    const char fat_str[] = "FAT";
    const char ammo_str[] = "Ammo: ";
    const char health_str[] = "Health: ";
    const char damage_str[] = "Damage: ";
    const char shootrate_str[] = "Shooting Rate: ";
    const char loadrate_str[] = "Loading rate: ";
    const OBSOLETE::shiptype fast {70, 14, 40, 400, 1700};
    const OBSOLETE::shiptype med {120, 10, 30, 500, 2000};
    const OBSOLETE::shiptype fat {240, 8, 25, 600, 2200};

    m_screen->setCursor(30,50);
    m_screen->setTextColor(Common::Ui::WHITE);
    m_screen->setTextSize(3);
    m_screen->print(fast_str, sizeof(fast_str));
    
    m_screen->setCursor(160,50);
    m_screen->print(med_str, sizeof(med_str));

    m_screen->setCursor(320,50);
    m_screen->print(fat_str, sizeof(fat_str));

    m_screen->setTextSize(1);
    m_screen->setCursor(30,90);
    m_screen->print(health_str, sizeof(health_str));
    m_screen->print(fast.health);

    m_screen->setCursor(30,100);
    m_screen->print(ammo_str, sizeof(ammo_str));
    m_screen->print(fast.ammo);

    m_screen->setCursor(30,110);
    m_screen->print(damage_str, sizeof(damage_str));
    m_screen->print(fast.damage);

    m_screen->setCursor(30,120);
    m_screen->print(shootrate_str, sizeof(shootrate_str));
    m_screen->print(fast.shootrate);

    m_screen->setCursor(30,130);
    m_screen->print(loadrate_str, sizeof(loadrate_str));
    m_screen->print(fast.loadrate);


    m_screen->setCursor(160,90);
    m_screen->print(health_str, sizeof(health_str));
    m_screen->print(med.health);

    m_screen->setCursor(160,100);
    m_screen->print(ammo_str, sizeof(ammo_str));
    m_screen->print(med.ammo);

    m_screen->setCursor(160,110);
    m_screen->print(damage_str, sizeof(damage_str));
    m_screen->print(med.damage);

    m_screen->setCursor(160,120);
    m_screen->print(shootrate_str, sizeof(shootrate_str));
    m_screen->print(med.shootrate);

    m_screen->setCursor(160,130);
    m_screen->print(loadrate_str, sizeof(loadrate_str));
    m_screen->print(med.loadrate);


    m_screen->setCursor(320,90);
    m_screen->print(health_str, sizeof(health_str));
    m_screen->print(fat.health);

    m_screen->setCursor(320,100);
    m_screen->print(ammo_str, sizeof(ammo_str));
    m_screen->print(fat.ammo);

    m_screen->setCursor(320,110);
    m_screen->print(damage_str, sizeof(damage_str));
    m_screen->print(fat.damage);

    m_screen->setCursor(320,120);
    m_screen->print(shootrate_str, sizeof(shootrate_str));
    m_screen->print(fat.shootrate);

    m_screen->setCursor(320,130);
    m_screen->print(loadrate_str, sizeof(loadrate_str));
    m_screen->print(fat.loadrate);
 
    m_screen->drawRect(25,45,120,150,Common::Ui::WHITE);    
    
    int i = 0;
    while(digitalRead(enter) == LOW) {
        if(i == 0) {
            if (digitalRead(right) == HIGH) {
                i = 1;
                m_screen->drawRect(25,45,120,150,Common::Ui::BLACK);
                m_screen->drawRect(155,45,120,150,Common::Ui::WHITE);
                delay(200);
            } else {
                delay(10);
            }
        } else if (i == 2) {
            if (digitalRead(left) == HIGH) {
                i = 1;
                m_screen->drawRect(315,45,120,150,Common::Ui::BLACK);
                m_screen->drawRect(155,45,120,150,Common::Ui::WHITE);
                delay(200);
            } else {
                delay(10);
            }
        } else if (i == 1) {
            if (digitalRead(left) == HIGH) {
                i = 0;
                m_screen->drawRect(155,45,120,150,Common::Ui::BLACK);
                m_screen->drawRect(25,45,120,150,Common::Ui::WHITE);
                delay(200);
            } else if (digitalRead(right) == HIGH) {
                i = 2;
                m_screen->drawRect(155,45,120,150,Common::Ui::BLACK);
                m_screen->drawRect(315,45,120,150,Common::Ui::WHITE);
                delay(200);     
            } else {
                delay(10);
            }
        }   
    }
    if (i == 0) {
        return fast;
    } else if (i == 1) {
        return med;
    } else {
        return fat;
    }
}

} // namespace Ui
