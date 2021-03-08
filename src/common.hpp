#ifndef COMMON_HPP
#define COMMON_HPP

#include "Arduino.h"

#include <stdint.h>

namespace Common {

enum GameErrors
{
    NoError,
    UiError,
    SetupError,
    RunTimeError,
    UnknownError
};

enum GameState 
{
    GameStopped,
    GameInSetup,
    GameStarted,
    GameEnded,
    GameError
};

enum Players
{
    Player1,
    Player2,
    PLAYER_COUNT
};

namespace UpdateRates {
namespace Micros {
namespace Constants
{
    const uint32_t screenUpdateRate = 30000;
    const uint32_t shipUpdateRate = 15000;
    const uint32_t bulletUpdateRate = 3000;
}
}
}

namespace Ui {
// constants for array sizes
const int bulletCount   = 32;
const int hitPixelCount = 10;

// play area size
const int16_t courtSizeXmin = 50;
const int16_t courtSizeYmin = 40;
const int16_t courtSizeXmax = 430;
const int16_t courtSizeYmax = 280;

// start coordinates
const uint16_t PLAYER_1_X = Common::Ui::courtSizeXmin + 20;
const uint16_t PLAYER_2_X = Common::Ui::courtSizeXmax - 20;
const uint16_t PLAYER_1_Y = Common::Ui::courtSizeYmin + 100;
const uint16_t PLAYER_2_Y = Common::Ui::courtSizeYmin + 50;

enum Color
{
    // Color definitions
    BLACK   = 0x0000,
    BLUE    = 0x001F,
    RED     = 0xF800,
    GREEN   = 0x07E0,
    CYAN    = 0x07FF,
    MAGENTA = 0xF81F,
    YELLOW  = 0xFFE0,  
    WHITE   = 0xFFFF
};

const Color PlayerColors[Common::Players::PLAYER_COUNT] = {GREEN, RED};

enum Button
{
    PLAYER_1_BUTTON_LEFT    = 53,
    PLAYER_1_BUTTON_RIGHT   = 52,
    PLAYER_1_BUTTON_SHOOT   = 51,
    PLAYER_2_BUTTON_LEFT    = 50,
    PLAYER_2_BUTTON_RIGHT   = 49,
    PLAYER_2_BUTTON_SHOOT   = 48,
    ENTER_BUTTON            = 47   
};

enum ButtonPresses
{
    Right,
    Left,
    Shoot,
    ButtonCount // per player
};

namespace Adafruit {

static const uint8_t LCD_CS = 57; // Chip Select goes to Analog 3 (A3)
static const uint8_t LCD_CD = 56; // Command/Data goes to Analog 2 (A2)
static const uint8_t LCD_WR = 55; // LCD Write goes to Analog 1 (A1)
static const uint8_t LCD_RD = 54; // LCD Read goes to Analog 0 (A0)
static const uint8_t LCD_RST = 58; // reset analog 4 (A4)

// #define LCD_CS  A3 // Chip Select goes to Analog 3
// #define LCD_CD  A2 // Command/Data goes to Analog 2
// #define LCD_WR  A1 // LCD Write goes to Analog 1
// #define LCD_RD  A0 // LCD Read goes to Analog 0
// #define LCD_RST A4 // reset
}

namespace ConstantCoordinates {
    const int16_t Player1HealthX = 100;
    const int16_t Player1HealthY = 30;
    const int16_t Player1AmmoX = 98;
    const int16_t Player1AmmoY = 285;
    const int16_t Player2HealthX = 410;
    const int16_t Player2HealthY = 30;
    const int16_t Player2AmmoX = 410;
    const int16_t Player2AmmoY = 285;

    const int16_t statrectsizeX = 30;
    const int16_t statrectsizeY = 10;
}

} // namespace ui

enum SpecificationRanges 
{
    HealthMin       = 50,
    HealthMax       = 250,
    AmmoMin         = 5,
    AmmoMax         = 20,
    DamageMin       = 20,
    DamageMax       = 50,
    ShootRateMin    = 400,
    ShootRateMax    = 600,
    LoadRateMin     = 1500,
    LoadRateMax     = 2500
};

struct Coordinates 
{
    uint16_t x_coord;
    uint16_t y_coord;
};

} // namespace common



namespace OBSOLETE {

struct shiptype {
    int health;
    int ammo;
    int damage;
    unsigned long shootrate;
    unsigned long loadrate;
};

} // namespace OBSOLETE

#endif