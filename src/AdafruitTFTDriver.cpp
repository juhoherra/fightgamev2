#include "AdafruitTFTDriver.hpp"
#include "common.hpp"


namespace Adafruit {

AdafruitTFTDriver::AdafruitTFTDriver() :
    m_tft(new Adafruit_TFTLCD(Common::Ui::Adafruit::LCD_CS, 
                              Common::Ui::Adafruit::LCD_CD,
                              Common::Ui::Adafruit::LCD_WR,
                              Common::Ui::Adafruit::LCD_RD,
                              Common::Ui::Adafruit::LCD_RST))
{

}

AdafruitTFTDriver::~AdafruitTFTDriver()
{
    delete m_tft;
}

void AdafruitTFTDriver::reset() 
{
    m_tft->reset();
}

uint16_t AdafruitTFTDriver::readID() 
{
    return m_tft->readID();
}

void AdafruitTFTDriver::begin(uint16_t identifier) 
{
    m_tft->begin(identifier);
}

void AdafruitTFTDriver::setRotation(int rot) 
{
    m_tft->setRotation(rot);
}

void AdafruitTFTDriver::drawCircle(int16_t x, int16_t y, int16_t radius, uint16_t color) 
{
    m_tft->drawCircle(x, y, radius, color);
}

void AdafruitTFTDriver::drawPixel(int16_t x, int16_t y, uint16_t color) 
{
    m_tft->drawPixel(x, y, color);
}

void AdafruitTFTDriver::drawRect(int16_t x, int16_t y, int16_t size_x, int16_t size_y, uint16_t color) 
{
    m_tft->drawRect(x, y, size_x, size_y, color);
}

void AdafruitTFTDriver::drawVLine(int16_t x, int16_t y, int16_t lenght, uint16_t color) 
{
    m_tft->drawFastVLine(x, y, lenght, color);
}

void AdafruitTFTDriver::drawHLine(int16_t x, int16_t y, int16_t lenght, uint16_t color) 
{
    m_tft->drawFastHLine(x, y, lenght, color);
}

void AdafruitTFTDriver::fillRect(int16_t x, int16_t y, int16_t size_x, int16_t size_y, uint16_t color) 
{
    m_tft->fillRect(x, y, size_x, size_y, color);
}

void AdafruitTFTDriver::fillScreen(uint16_t color) 
{
    m_tft->fillScreen(color);
}

void AdafruitTFTDriver::setCursor(int16_t x, int16_t y) 
{
    m_tft->setCursor(x, y);
}

void AdafruitTFTDriver::setTextColor(uint16_t color) 
{
    m_tft->setTextColor(color);
}

void AdafruitTFTDriver::setTextSize(int size) 
{
    m_tft->setTextSize(size);
}

void AdafruitTFTDriver::print(const char* text, const size_t text_lenght) 
{
    String text_to_be_written;
    const char* text_ptr = text;
    for (size_t i = 0; i < text_lenght; i++)
    {
        text_to_be_written += text[i];
    }
    // for (auto chr : text_to_be_written)
    // {
    //      chr = *text_ptr;
    //      text_ptr++;
    // }
    m_tft->print(text_to_be_written);
}

void AdafruitTFTDriver::print(int num)
{
    m_tft->print(num); 
}

} // namespace Adafruit