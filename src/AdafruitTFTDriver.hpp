#ifndef ADAFRUITTFTDRIVER_HPP
#define ADAFRUITTFTDRIVER_HPP

#include "IScreen.hpp"

#include <Adafruit_TFTLCD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <gfxfont.h>

namespace Adafruit {

class AdafruitTFTDriver : public IScreen
{

public:
    AdafruitTFTDriver();
    ~AdafruitTFTDriver();

    virtual void reset() override;
    virtual uint16_t readID() override;
    virtual void begin(uint16_t identifier) override;
    virtual void setRotation(int rot) override;

    virtual void drawCircle(int16_t x, int16_t y, int16_t radius, uint16_t color) override;
    virtual void drawPixel(int16_t x, int16_t y, uint16_t color) override;
    virtual void drawRect(int16_t x, int16_t y, int16_t size_x, int16_t size_y, uint16_t color) override;
    virtual void drawVLine(int16_t x, int16_t y, int16_t lenght, uint16_t color) override;
    virtual void drawHLine(int16_t x, int16_t y, int16_t lenght, uint16_t color) override;

    virtual void fillRect(int16_t x, int16_t y, int16_t size_x, int16_t size_y, uint16_t color) override;
    virtual void fillScreen(uint16_t color) override;

    virtual void setCursor(int16_t x, int16_t y) override;
    virtual void setTextColor(uint16_t color) override;
    virtual void setTextSize(int size) override;
    virtual void print(const char* text, const size_t text_lenght) override;
    virtual void print(int num) override;

private:
    Adafruit_TFTLCD* m_tft;
};

}


#endif