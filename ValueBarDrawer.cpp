#include "ValueBarDrawer.h"
#include "HALFpSim.h"

const WidgetTypes::Display::ColorRGB ValueBarDrawer::ClearColor = {0,0,0};


ValueBarDrawer::ValueBarDrawer(uint8_t x,
                   uint8_t y,
                   uint8_t w,
                   uint8_t h,
                   int16_t valueRangeMin,
                   int16_t valueRangeMax,
                   WidgetTypes::Display::ColorRGB frameColor,
                   WidgetTypes::Display::ColorRGB barColorBegin,
                   WidgetTypes::Display::ColorRGB barColorEnd,
                   HALFpSim &display,
                   const DisplayWidget& widget) : m_frame(x, y, w, h),
                                                m_bar(x + 1, y + 1, w - 2, h - 2),
                                                m_valueRangeMin(valueRangeMin),
                                                m_valueRangeMax(valueRangeMax),
                                                m_frameColor(frameColor),
                                                m_barColorBegin(barColorBegin),
                                                m_barColorEnd(barColorEnd),
                                                m_rDisplay(display),
                                                m_widget(widget),
                                                m_valuePosXLast(0),
                                                m_modulatedValuePosXLast(0)
{
}

void ValueBarDrawer::initialDraw()
{
    m_rDisplay.displayDrawRectangle(m_widget,
                                    WidgetTypes::Display::Coord(m_frame.x, m_frame.y-6),
                                    m_frame.w,
                                    m_frame.h + 12,
                                    {0,0,0},
                                    true);
    m_rDisplay.displayDrawRectangle(m_widget,
                                    WidgetTypes::Display::Coord(m_frame.x, m_frame.y),
                                    m_frame.w,
                                    m_frame.h,
                                    m_frameColor);
}

void ValueBarDrawer::draw(int16_t value, int16_t modulation)
{
    value = std::max(m_valueRangeMin, value);
    value = std::min(m_valueRangeMax, value);
    uint8_t valuePosX = map<int16_t>(value, m_valueRangeMin, m_valueRangeMax, 0, m_bar.w - 1);

    int16_t modulatedValue = value + modulation;
    modulatedValue = std::max(m_valueRangeMin, modulatedValue);
    modulatedValue = std::min(m_valueRangeMax, modulatedValue);
    uint8_t modulatedValuePosX = map<int16_t>(modulatedValue, m_valueRangeMin, m_valueRangeMax, 0, m_bar.w - 1);

    if (modulatedValuePosX > m_modulatedValuePosXLast)
    {
        for (int i = m_modulatedValuePosXLast; i <= modulatedValuePosX; ++i)
        {
            const int Xpos = m_bar.x + i;
            uint8_t red = map<int16_t>(i, 0, m_bar.w, m_barColorBegin.r, m_barColorEnd.r);
            uint8_t green = map<int16_t>(i, 0, m_bar.w, m_barColorBegin.g, m_barColorEnd.g);
            uint8_t blue = map<int16_t>(i, 0, m_bar.w, m_barColorBegin.b, m_barColorEnd.b);
            m_rDisplay.displayDrawLine( m_widget,
                                        WidgetTypes::Display::Coord( Xpos, m_bar.y ),
                                        WidgetTypes::Display::Coord( Xpos, m_bar.y + m_bar.h - 1 ),
                                        {red, green, blue});
        }
    }
    else if (modulatedValuePosX < m_modulatedValuePosXLast)
    {
        for (int i = m_modulatedValuePosXLast; i > modulatedValuePosX; --i)
        {
            const int Xpos = m_bar.x + i;
            m_rDisplay.displayDrawLine( m_widget,
                                        WidgetTypes::Display::Coord( Xpos, m_bar.y ),
                                        WidgetTypes::Display::Coord( Xpos, m_bar.y + m_bar.h - 1 ),
                                        ClearColor );
        }
    }

    if (valuePosX != m_valuePosXLast)
    {
        const int XposNew = m_bar.x + valuePosX;
        const int XposOld = m_bar.x + m_valuePosXLast;
        m_rDisplay.displayDrawVLine(m_widget,
                                    WidgetTypes::Display::Coord( XposOld, m_frame.y - MidLineHeight),
                                    MidLineHeight,
                                    ClearColor);
        m_rDisplay.displayDrawVLine(m_widget,
                                    WidgetTypes::Display::Coord( XposNew, m_frame.y - MidLineHeight),
                                    MidLineHeight,
                                    m_frameColor);
        m_rDisplay.displayDrawVLine(m_widget, 
                                    WidgetTypes::Display::Coord(XposOld, m_frame.y + m_frame.h),
                                    MidLineHeight,
                                    ClearColor);
        m_rDisplay.displayDrawVLine(m_widget,
                                    WidgetTypes::Display::Coord(XposNew, m_frame.y + m_frame.h),
                                    MidLineHeight,
                                    m_frameColor);
    }

    m_modulatedValuePosXLast = modulatedValuePosX;
    m_valuePosXLast = valuePosX;
}
