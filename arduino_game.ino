#include "src/Game.hpp"

// remeber to change Adafruit_TFTLCD.cpp
// #define TFTWIDTH 320
// #define TFTHEIGHT 480

#define DEBUG

void setup() {
  // put your setup code here, to run once:
  Game game;
  int returnCode = game.setup();
  if (!returnCode)
  {
    game.run();
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
