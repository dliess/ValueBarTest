#include "TextField.h"
#include "HALFpSim.h"
#include <stdio.h> // snprintf()


TextField::TextField(   HALFpSim&                             rDisplay,
                        const DisplayWidget&                  widget,
                        const WidgetTypes::Display::Coord&    upLeftPos,
                        const WidgetTypes::Display::Size2D&   size,
                        const WidgetTypes::Display::FontId&   fontId,
                        const WidgetTypes::Display::FontSize& fontSize,
                        const WidgetTypes::Display::ColorRGB& color,
                        HPlacement                            hPlacement,
                        VPlacement                            vPlacement  ):
    m_rDisplay(rDisplay),
    m_widget(widget),
    m_upLeftPos(upLeftPos),
    m_size(size),
    m_fontId(fontId),
    m_fontSize(fontSize),
    m_color(color),
    m_hPlacement(hPlacement),
    m_vPlacement(vPlacement),
    m_lastStrPos({0,0}),
    m_lastStrSize({0,0})
    {}

void TextField::draw(int32_t value)
{
    draw(value, m_color);
}

void TextField::draw(int32_t value, const WidgetTypes::Display::ColorRGB& color)
{
    clearPrev();
    m_rDisplay.displaySetFont(m_widget, m_fontId, m_fontSize);
    char strBuf[64];
    snprintf(strBuf, sizeof(strBuf), "%d", value);
    WidgetTypes::Display::Size2D strSize = m_rDisplay.displayGetTextSize(m_widget, strBuf);
    WidgetTypes::Display::Coord strPos;
    switch(m_hPlacement)
    {
        case HPlacement::AlignLeft:
            strPos.x = m_upLeftPos.x;
            break;
        case HPlacement::AlignRight:
            strPos.x = m_upLeftPos.x + (m_size.w - strSize.w);
            break;
        case HPlacement::AlignCenter:
            strPos.x = m_upLeftPos.x + ((m_size.w - strSize.w) / 2);
            break;
    }
    switch(m_vPlacement)
    {
        case VPlacement::AlignTop:
            strPos.y = m_upLeftPos.y;
            break;
        case VPlacement::AlignBottom:
            strPos.y = m_upLeftPos.y + (m_size.h - (strSize.h));
            break;
        case VPlacement::AlignCenter:
            strPos.y = m_upLeftPos.y + ((m_size.h - (strSize.h)) / 2) - 2;
            break;
    }
    m_rDisplay.displayDrawText( m_widget,
                                strPos,
                                color,
                                strBuf );
    m_lastStrPos  = strPos;                            
    m_lastStrSize = strSize;
}

void TextField::clearPrev()
{
    m_rDisplay.displayDrawRectangle(m_widget,
                                    WidgetTypes::Display::Coord(m_lastStrPos),
                                    WidgetTypes::Display::Size2D(m_lastStrSize),
                                    {0,0,0},
                                    true);
}

void TextField::drawFieldBorder(const WidgetTypes::Display::ColorRGB& color)
{
    m_rDisplay.displayDrawRectangle(m_widget,
                                    WidgetTypes::Display::Coord({m_upLeftPos.x - 1, m_upLeftPos.y - 1}),
                                    WidgetTypes::Display::Size2D({m_size.w + 2, m_size.h + 2}),
                                    color,
                                    false);
}

void TextField::clear(const WidgetTypes::Display::ColorRGB& clearColor)
{
    m_rDisplay.displayDrawRectangle(m_widget,
                                    WidgetTypes::Display::Coord({m_upLeftPos.x - 1, m_upLeftPos.y - 1}),
                                    WidgetTypes::Display::Size2D({m_size.w + 2, m_size.h + 2}),
                                    clearColor,
                                    true);
}
