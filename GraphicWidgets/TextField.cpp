#include "TextField.h"
#include "DisplayRenderInterface.h"
#include <stdio.h> // snprintf()
#include "RenderIf.h"


TextField::TextField(   const fpw::Display::Coord&    upLeftPos,
                        const fpw::Display::Size2D&   size,
                        const GFXfont&                rFont,
                        uint8_t                       fontScaleFactor,
                        const fpw::Display::ColorRGB& color,
                        HPlacement                    hPlacement,
                        VPlacement                    vPlacement  ):
    m_upLeftPos(upLeftPos),
    m_size(size),
    m_pFont(&rFont),
    m_fontScaleFactor(fontScaleFactor),
    m_color(color),
    m_hPlacement(hPlacement),
    m_vPlacement(vPlacement),
    m_lastStrPos({0,0}),
    m_lastStrSize({0,0})
    {}

void TextField::draw(RenderIf& r, const std::string& txt)
{
    draw(r, txt, m_color);
}

void TextField::draw(RenderIf& r, const std::string& txt, const fpw::Display::ColorRGB& color)
{
    //clearPrev(r);
    r.setFont(*m_pFont, m_fontScaleFactor);
    fpw::Display::Size2D    strSize;
    fpw::Display::Offset2D  strOffset;
    r.getRenderedTextSize(txt, nullptr, strSize, strOffset);
    fpw::Display::Coord txtMidLinePos;
    const int32_t widthDiff = static_cast<int32_t>(m_size.w) - static_cast<int32_t>(strSize.w);
    const int32_t heightDiff = static_cast<int32_t>(m_size.h) - static_cast<int32_t>(strSize.h);

    switch(m_hPlacement)
    {
        case HPlacement::AlignLeft:
            txtMidLinePos.x = m_upLeftPos.x;
            break;
        case HPlacement::AlignRight:
            txtMidLinePos.x = m_upLeftPos.x + widthDiff;
            break;
        case HPlacement::AlignCenter:
            txtMidLinePos.x = m_upLeftPos.x + (widthDiff / 2);
            break;
    }
    switch(m_vPlacement)
    {
        case VPlacement::AlignTop:
            txtMidLinePos.y = m_upLeftPos.y;
            break;
        case VPlacement::AlignBottom:
            txtMidLinePos.y = m_upLeftPos.y + m_size.h - strSize.h;
            break;
        case VPlacement::AlignCenter:
            txtMidLinePos.y = m_upLeftPos.y + (heightDiff / 2);
            break;
    }
    txtMidLinePos = {txtMidLinePos.x - strOffset.x, txtMidLinePos.y - strOffset.y};
    //r.drawRectangle({txtMidLinePos + strOffset, strSize}, {255,255,255}, false);
    r.drawText(txtMidLinePos, color, txt);
    m_lastStrPos  = txtMidLinePos;                            
    m_lastStrSize = strSize;
}

void TextField::clearPrev(RenderIf& r)
{
    r.drawRectangle(fpw::Display::Rectangle( m_lastStrPos, m_lastStrSize ),
                                   {0,0,0},
                                   true);
}

void TextField::drawFieldBorder(RenderIf& r, const fpw::Display::ColorRGB& color)
{
    r.drawRectangle(fpw::Display::Rectangle(
                                        fpw::Display::Coord({m_upLeftPos.x - 1, m_upLeftPos.y - 1}),
                                        fpw::Display::Size2D({m_size.w + 2, m_size.h + 2})),
                                   color,
                                   false);
}

void TextField::clear(RenderIf& r, const fpw::Display::ColorRGB& clearColor)
{
    r.drawRectangle(fpw::Display::Rectangle(
                                        fpw::Display::Coord({m_upLeftPos.x - 1, m_upLeftPos.y - 1}),
                                        fpw::Display::Size2D({m_size.w + 2, m_size.h + 2})),
                                   clearColor,
                                   true);
}

void TextField::setHPlacement(HPlacement hPlacement)
{
    m_hPlacement = hPlacement;
}

void TextField::setVPlacement(VPlacement vPlacement)
{
    m_vPlacement = vPlacement;
}

void TextField::setFont(const GFXfont& font, uint8_t scale)
{
    m_pFont = &font;
    m_fontScaleFactor = scale;
}
