#ifndef VALUE_DRAWER_H
#define VALUE_DRAWER_H

#include <cstdint>
#include "FpWidgetOut_Spec.h"

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
                const fpw::Display::Coord&    upLeftPos,
                const fpw::Display::Size2D&   size,
                const fpw::Display::FontId&   fontId,
                const fpw::Display::FontSize& fontSize,
                const fpw::Display::ColorRGB& color,
                HPlacement                            hPlacement = HPlacement::AlignLeft,
                VPlacement                            vPlacement = VPlacement::AlignTop  );

    void draw(int32_t value);
    void draw(int32_t value, const fpw::Display::ColorRGB& color);
    void drawFieldBorder(const fpw::Display::ColorRGB& color);
    void clear(const fpw::Display::ColorRGB& clearColor = {0,0,0});



private:
    HALFpSim&                       m_rDisplay;
    DisplayWidget                   m_widget;
    fpw::Display::Coord     m_upLeftPos;
    fpw::Display::Size2D    m_size;
    fpw::Display::FontId    m_fontId;
    fpw::Display::FontSize  m_fontSize;
    fpw::Display::ColorRGB  m_color;
    HPlacement                      m_hPlacement;
    VPlacement                      m_vPlacement;

    fpw::Display::Coord     m_lastStrPos;
    fpw::Display::Size2D    m_lastStrSize;

    void clearPrev();
};

#endif