#ifndef _VALUE_BAR_DRAWER_H
#define _VALUE_BAR_DRAWER_H

#include <cstdint>
#include "FpWidgetOut_Spec.h"

class DisplayInterface;
struct Rect
{
    Rect(uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h) : x(_x), y(_y), w(_w), h(_h){};
    uint8_t x, y, w, h;
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
             fpw::Display::ColorRGB frameColor,
             fpw::Display::ColorRGB barColorBegin,
             fpw::Display::ColorRGB barColorEnd);
    void initialDraw();
    void draw(DisplayInterface& displayInterface, int16_t value, int16_t modulation = 0);

  private:
    bool m_initialDraw;
    Rect m_frame;
    Rect m_bar;
    int16_t m_valueRangeMin;
    int16_t m_valueRangeMax;
    fpw::Display::ColorRGB m_frameColor;
    
    fpw::Display::ColorRGB m_barColorBegin;
    fpw::Display::ColorRGB m_barColorEnd;
    static const fpw::Display::ColorRGB ClearColor;
    static const uint16_t MidLineHeight = 4;
    uint8_t m_valuePosXLast;
    uint8_t m_modulatedValuePosXLast;

    template<typename T>
    T map(T value, T valueMin, T valueMax, T rangeMin, T rangeMax)
    {
      T deltaVal = value - valueMin;
      T valWholeLength = valueMax - valueMin;
      T newWholeLength = rangeMax - rangeMin;
      return (deltaVal * newWholeLength / valWholeLength) + rangeMin;
    //return ( (value - valueMin) / (valueMax - valueMin) ) * (rangeMax - rangeMin) + rangeMin;
    }
};

#endif