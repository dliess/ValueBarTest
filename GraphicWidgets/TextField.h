#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include <cstdint>
#include "FpWidgetOut_Spec.h"
#include "Font.h"
#include <string>

class RenderIf;

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
    TextField(  const fpw::Display::Coord&    upLeftPos,
                const fpw::Display::Size2D&   size,
                const GFXfont&                rFont,
                uint8_t                       fontScaleFactor,
                const fpw::Display::ColorRGB& color,
                HPlacement hPlacement = HPlacement::AlignLeft,
                VPlacement vPlacement = VPlacement::AlignTop  );

    void draw(RenderIf& r, const std::string& txt);
    void draw(RenderIf& r, const std::string& txt, const fpw::Display::ColorRGB& color);
    void drawFieldBorder(RenderIf& r, const fpw::Display::ColorRGB& color);
    void clear(RenderIf& r, const fpw::Display::ColorRGB& clearColor = {0,0,0});

    void setHPlacement(HPlacement hPlacement);
    void setVPlacement(VPlacement vPlacement);
    void setFont(const GFXfont& font, uint8_t scale = 1);


private:
    fpw::Display::Coord     m_upLeftPos;
    fpw::Display::Size2D    m_size;
    const GFXfont*          m_pFont;
    uint8_t                 m_fontScaleFactor;
    fpw::Display::ColorRGB  m_color;
    HPlacement              m_hPlacement;
    VPlacement              m_vPlacement;

    fpw::Display::Coord     m_lastStrPos;
    fpw::Display::Size2D    m_lastStrSize;

    void clearPrev(RenderIf& r);
};

#endif