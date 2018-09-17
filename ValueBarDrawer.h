#ifndef _VALUE_BAR_DRAWER_H
#define _VALUE_BAR_DRAWER_H

#include <cstdint>
#include "Widget_Spec.h"
#include "WidgetTypes.h"

class HALFpSim;
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
             WidgetTypes::Display::ColorRGB frameColor,
             WidgetTypes::Display::ColorRGB barColorBegin,
             WidgetTypes::Display::ColorRGB barColorEnd,
             HALFpSim &display,
             const DisplayWidget& widget);
    void initialDraw();
    void draw(int16_t value, int16_t modulation = 0);

  private:
    Rect m_frame;
    Rect m_bar;
    int16_t m_valueRangeMin;
    int16_t m_valueRangeMax;
    WidgetTypes::Display::ColorRGB m_frameColor;
    
    WidgetTypes::Display::ColorRGB m_barColorBegin;
    WidgetTypes::Display::ColorRGB m_barColorEnd;
    HALFpSim &m_rDisplay;
    DisplayWidget m_widget;
    static const WidgetTypes::Display::ColorRGB ClearColor;
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