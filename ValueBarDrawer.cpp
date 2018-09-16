#include "ValueBarDrawer.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>

uint8_t swapNibbles(uint8_t val)
{
   uint8_t data = val >> 4;
   data |= ((val & 0x0F) << 4);
   return data;;
}


ValueBarDrawer::ValueBarDrawer(uint8_t x,
                   uint8_t y,
                   uint8_t w,
                   uint8_t h,
                   int16_t valueRangeMin,
                   int16_t valueRangeMax,
                   uint16_t frameColor,
                   uint16_t barColorBegin,
                   uint16_t barColorEnd,
                   Adafruit_SSD1331 &display) : m_frame(x, y, w, h),
                                                m_bar(x + 1, y + 1, w - 2, h - 2),
                                                m_valueRangeMin(valueRangeMin),
                                                m_valueRangeMax(valueRangeMax),
                                                m_frameColor(frameColor),
                                                m_barColorBegin(barColorBegin),
                                                m_barColorEnd(barColorEnd),
                                                m_rDisplay(display),
                                                m_valuePosXLast(0),
                                                m_modulatedValuePosXLast(0)
{
}

void ValueBarDrawer::initialDraw()
{
    m_rDisplay.drawRect(m_frame.x, m_frame.y, m_frame.w, m_frame.h, m_frameColor);
}

void ValueBarDrawer::draw(int16_t value, int16_t modulation)
{
    value = max(m_valueRangeMin, value);
    value = min(m_valueRangeMax, value);
    uint8_t valuePosX = map(value, m_valueRangeMin, m_valueRangeMax, 0, m_bar.w - 1);

    int16_t modulatedValue = value + modulation;
    modulatedValue = max(m_valueRangeMin, modulatedValue);
    modulatedValue = min(m_valueRangeMax, modulatedValue);
    uint8_t modulatedValuePosX = map(modulatedValue, m_valueRangeMin, m_valueRangeMax, 0, m_bar.w - 1);

    if (modulatedValuePosX > m_modulatedValuePosXLast)
    {
        for (int i = m_modulatedValuePosXLast; i <= modulatedValuePosX; ++i)
        {
            const int Xpos = m_bar.x + i;
            uint8_t red = map(i, 0, m_bar.w, m_barColorBegin.red, m_barColorEnd.red);
            uint8_t green = map(i, 0, m_bar.w, m_barColorBegin.green, m_barColorEnd.green);
            uint8_t blue = map(i, 0, m_bar.w, m_barColorBegin.blue, m_barColorEnd.blue);

            uint16_t color = Adafruit_SSD1331::Color565(swapNibbles(red >> 1), swapNibbles(green >> 2), swapNibbles(blue >> 1));

            m_rDisplay.drawLine(Xpos, m_bar.y, Xpos, m_bar.y + m_bar.h - 1, color);
        }
    }
    else if (modulatedValuePosX < m_modulatedValuePosXLast)
    {
        for (int i = m_modulatedValuePosXLast; i > modulatedValuePosX; --i)
        {
            const int Xpos = m_bar.x + i;
            m_rDisplay.drawLine(Xpos, m_bar.y, Xpos, m_bar.y + m_bar.h - 1, ClearColor);
        }
    }

    if (valuePosX != m_valuePosXLast)
    {
        const int XposNew = m_bar.x + valuePosX;
        const int XposOld = m_bar.x + m_valuePosXLast;
        m_rDisplay.drawFastVLine(XposOld, m_frame.y - MidLineHeight, MidLineHeight, ClearColor);
        m_rDisplay.drawFastVLine(XposNew, m_frame.y - MidLineHeight, MidLineHeight, m_frameColor);
        m_rDisplay.drawFastVLine(XposOld, m_frame.y + m_frame.h, MidLineHeight, ClearColor);
        m_rDisplay.drawFastVLine(XposNew, m_frame.y + m_frame.h, MidLineHeight, m_frameColor);
    }

    m_modulatedValuePosXLast = modulatedValuePosX;
    m_valuePosXLast = valuePosX;
}
