#ifndef VALUE_DRAWER_H
#define VALUE_DRAWER_H

#include <cstdint>
#include "WidgetTypes.h"
#include "Widget_Spec.h"

class HALFpSim;

class ValueDrawer
{
public:
    ValueDrawer(HALFpSim&                             rDisplay,
                const DisplayWidget&                  widget,
                const WidgetTypes::Display::Coord&    upLeftPos,
                uint16_t                              w,
                uint16_t                              h,
                const WidgetTypes::Display::FontId&   fontId,
                const WidgetTypes::Display::ColorRGB& color);

    void draw(int32_t value);

private:
    HALFpSim&                       m_rDisplay;
    DisplayWidget                   m_widget;
    WidgetTypes::Display::Coord     m_upLeftPos;
    uint16_t                        m_w;
    uint16_t                        m_h;
    WidgetTypes::Display::FontId    m_fontId;
    WidgetTypes::Display::ColorRGB  m_color;
};

#endif