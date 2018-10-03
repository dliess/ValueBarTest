#include "TextField.h"
#include "DisplayInterface.h"
#include <stdio.h> // snprintf()

TextField::TextField(   const fpw::Display::Coord&    upLeftPos,
                        const fpw::Display::Size2D&   size,
                        const GFXfont&                rFont,
                        const fpw::Display::ColorRGB& color,
                        HPlacement                    hPlacement,
                        VPlacement                    vPlacement  ):
    m_upLeftPos(upLeftPos),
    m_size(size),
    m_rFont(rFont),
    m_color(color),
    m_hPlacement(hPlacement),
    m_vPlacement(vPlacement),
    m_lastStrPos({0,0}),
    m_lastStrSize({0,0})
    {}

void TextField::draw(DisplayInterface& displayInterface, int32_t value)
{
    draw(displayInterface, value, m_color);
}

void TextField::draw(DisplayInterface& displayInterface, int32_t value, const fpw::Display::ColorRGB& color)
{
    //clearPrev(displayInterface);
    displayInterface.setFont(m_rFont, 1);
    std::string txt = "q";
    txt += std::to_string(value);
    txt += "g";
    fpw::Display::Size2D    strSize;
    fpw::Display::Offset2D  strOffset;
    displayInterface.getRenderedTextSize(txt, nullptr, strSize, strOffset);
    fpw::Display::Coord strPos;
    const int32_t widthDiff = static_cast<int32_t>(m_size.w) - static_cast<int32_t>(strSize.w);
    const int32_t heightDiff = static_cast<int32_t>(m_size.h) - static_cast<int32_t>(strSize.h);

    switch(m_hPlacement)
    {
        case HPlacement::AlignLeft:
            strPos.x = m_upLeftPos.x;
            break;
        case HPlacement::AlignRight:
            strPos.x = m_upLeftPos.x + widthDiff;
            break;
        case HPlacement::AlignCenter:
            strPos.x = m_upLeftPos.x + (widthDiff / 2);
            break;
    }
    switch(m_vPlacement)
    {
        case VPlacement::AlignTop:
            strPos.y = m_upLeftPos.y + strSize.h;
            break;
        case VPlacement::AlignBottom:
            strPos.y = m_upLeftPos.y + m_size.h - 1;
            break;
        case VPlacement::AlignCenter:
            strPos.y = m_upLeftPos.y + (heightDiff / 2) + strSize.h;
            break;
    }
    strPos = {strPos.x - strOffset.x, strPos.y - strOffset.y};
    displayInterface.drawText(strPos, color, txt);
    m_lastStrPos  = strPos;                            
    m_lastStrSize = strSize;
}

void TextField::clearPrev(DisplayInterface& displayInterface)
{
    displayInterface.drawRectangle(fpw::Display::Rectangle( m_lastStrPos, m_lastStrSize ),
                                   {0,0,0},
                                   true);
}

void TextField::drawFieldBorder(DisplayInterface& displayInterface, const fpw::Display::ColorRGB& color)
{
    displayInterface.drawRectangle(fpw::Display::Rectangle(
                                        fpw::Display::Coord({m_upLeftPos.x - 1, m_upLeftPos.y - 1}),
                                        fpw::Display::Size2D({m_size.w + 2, m_size.h + 2})),
                                   color,
                                   false);
}

void TextField::clear(DisplayInterface& displayInterface, const fpw::Display::ColorRGB& clearColor)
{
    displayInterface.drawRectangle(fpw::Display::Rectangle(
                                        fpw::Display::Coord({m_upLeftPos.x - 1, m_upLeftPos.y - 1}),
                                        fpw::Display::Size2D({m_size.w + 2, m_size.h + 2})),
                                   clearColor,
                                   true);
}
