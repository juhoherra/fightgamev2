#ifndef ISCREEN_HPP
#define ISCREEN_HPP

#include <stdint.h>
#include <stdlib.h>

class IScreen
{
public:
    virtual void reset() = 0;
    virtual uint16_t readID() = 0;
    virtual void begin(uint16_t identifier) = 0;
    virtual void setRotation(int rot) = 0;
    
    virtual void drawCircle(int16_t x, int16_t y, int16_t radius, uint16_t color) = 0;
    virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;
    virtual void drawRect(int16_t x, int16_t y, int16_t size_x, int16_t size_y, uint16_t color) = 0;
    virtual void drawVLine(int16_t x, int16_t y, int16_t lenght, uint16_t color) = 0;
    virtual void drawHLine(int16_t x, int16_t y, int16_t lenght, uint16_t color) = 0;

    virtual void fillRect(int16_t x, int16_t y, int16_t size_x, int16_t size_y, uint16_t color) = 0;
    virtual void fillScreen(uint16_t color) = 0;

    virtual void setCursor(int16_t x, int16_t y) = 0;
    virtual void setTextColor(uint16_t color) = 0;
    virtual void setTextSize(int size) = 0;
    virtual void print(const char* text, const size_t text_lenght) = 0;
    virtual void print(int num) = 0;

};


#endif