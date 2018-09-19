#ifndef VALUE_DRAWER_H
#define VALUE_DRAWER_H

#include <cstdint>
#include "WidgetTypes.h"
#include "Widget_Spec.h"

class HALFpSim;

class TextField
{
public:
    TextField(  HALFpSim&                             rDisplay,
                const DisplayWidget&                  widget,
                const WidgetTypes::Display::Coord&    upLeftPos,
                uint16_t                              w,
                uint16_t                              h,
                const WidgetTypes::Display::FontId&   fontId,
                const WidgetTypes::Display::FontSize& fontSize,
                const WidgetTypes::Display::ColorRGB& color  );

    void draw(int32_t value);
    void draw(int32_t value, const WidgetTypes::Display::ColorRGB& color);


private:
    HALFpSim&                       m_rDisplay;
    DisplayWidget                   m_widget;
    WidgetTypes::Display::Coord     m_upLeftPos;
    uint16_t                        m_w;
    uint16_t                        m_h;
    WidgetTypes::Display::FontId    m_fontId;
    WidgetTypes::Display::FontSize  m_fontSize;
    WidgetTypes::Display::ColorRGB  m_color;

    WidgetTypes::Display::Coord     m_lastStrPos;
    WidgetTypes::Display::Size2D    m_lastStrSize;
};

#endif