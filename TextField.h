#ifndef VALUE_DRAWER_H
#define VALUE_DRAWER_H

#include <cstdint>
#include "WidgetTypes.h"
#include "Widget_Spec.h"

class HALFpSim;

class TextField
{
public:
    enum class HPlacement
    {
        AlignLeft   = 0,
        AlignRight  = 1,
        AlignCenter = 2
    };
    enum class VPlacement
    {
        AlignTop     = 0,
        AlignBottom  = 1,
        AlignCenter  = 2       
    };
    TextField(  HALFpSim&                             rDisplay,
                const DisplayWidget&                  widget,
                const WidgetTypes::Display::Coord&    upLeftPos,
                const WidgetTypes::Display::Size2D&   size,
                const WidgetTypes::Display::FontId&   fontId,
                const WidgetTypes::Display::FontSize& fontSize,
                const WidgetTypes::Display::ColorRGB& color,
                HPlacement                            hPlacement = HPlacement::AlignLeft,
                VPlacement                            vPlacement = VPlacement::AlignTop  );

    void draw(int32_t value);
    void draw(int32_t value, const WidgetTypes::Display::ColorRGB& color);
    void drawFieldBorder(const WidgetTypes::Display::ColorRGB& color);
    void clear(const WidgetTypes::Display::ColorRGB& clearColor = {0,0,0});



private:
    HALFpSim&                       m_rDisplay;
    DisplayWidget                   m_widget;
    WidgetTypes::Display::Coord     m_upLeftPos;
    WidgetTypes::Display::Size2D    m_size;
    WidgetTypes::Display::FontId    m_fontId;
    WidgetTypes::Display::FontSize  m_fontSize;
    WidgetTypes::Display::ColorRGB  m_color;
    HPlacement                      m_hPlacement;
    VPlacement                      m_vPlacement;

    WidgetTypes::Display::Coord     m_lastStrPos;
    WidgetTypes::Display::Size2D    m_lastStrSize;

    void clearPrev();
};

#endif