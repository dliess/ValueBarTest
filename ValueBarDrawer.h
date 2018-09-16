#ifndef _VALUE_BAR_DRAWER_H
#define _VALUE_BAR_DRAWER_H

#include <cstdint>

class Adafruit_SSD1331;
struct Rect
{
    Rect(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) : x(_x), y(_y), w(_w), h(_h){};
    uint8_t x, y, w, h;
};


struct RGB
{
   RGB(uint16_t colorCode) :
     red(colorCode >> 11),
     green((colorCode >> 5) & 0x3F),
     blue(colorCode & 0x1F)
     {}
   uint8_t red;
   uint8_t green;
   uint8_t blue;
};

class ValueBarDrawer
{
  public:
    ValueBarDrawer(uint8_t x,
             uint8_t y,
             uint8_t w,
             uint8_t h,
             int16_t valueRangeMin,
             int16_t valueRangeMax,
             uint16_t frameColor,
             uint16_t barColorBegin,
             uint16_t barColorEnd,
             Adafruit_SSD1331 &display);
    void initialDraw();
    void draw(int16_t value, int16_t modulation = 0);

  private:
    Rect m_frame;
    Rect m_bar;
    int16_t m_valueRangeMin;
    int16_t m_valueRangeMax;
    uint16_t m_frameColor;
    
    RGB m_barColorBegin;
    RGB m_barColorEnd;
    Adafruit_SSD1331 &m_rDisplay;
    static const uint16_t ClearColor = 0;
    static const uint16_t MidLineHeight = 4;
    uint8_t m_valuePosXLast;
    uint8_t m_modulatedValuePosXLast;
};

#endif