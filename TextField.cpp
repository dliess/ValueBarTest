#include "TextField.h"
#include "HALFpSim.h"
#include <stdio.h> // snprintf()


TextField::TextField(   HALFpSim&                             rDisplay,
                        const DisplayWidget&                  widget,
                        const WidgetTypes::Display::Coord&    upLeftPos,
                        uint16_t                              w,
                        uint16_t                              h,
                        const WidgetTypes::Display::FontId&   fontId,
                        const WidgetTypes::Display::FontSize& fontSize,
                        const WidgetTypes::Display::ColorRGB& color  ) :
    m_rDisplay(rDisplay),
    m_widget(widget),
    m_upLeftPos(upLeftPos),
    m_w(w),
    m_h(h),
    m_fontId(fontId),
    m_fontSize(fontSize),
    m_color(color)
    {}

void TextField::draw(int32_t value)
{
    m_rDisplay.displayDrawRectangle(m_widget,
                                    WidgetTypes::Display::Coord(m_upLeftPos),
                                    m_w,
                                    m_h,
                                    {0,0,0},
                                    true);
    m_rDisplay.displaySetFont(m_widget, m_fontId, m_fontSize);
    char strBuf[64];
    snprintf(strBuf, sizeof(strBuf), "%d", value);
    m_rDisplay.displayDrawText( m_widget,
                                m_upLeftPos,
                                m_color,
                                strBuf);
}