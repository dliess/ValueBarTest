#include "DisplayCb.h"
#include "DefaultMonospace.h"
#include "FreeMono9pt7b.h"
#include "FreeSansOblique9pt7b.h"
#include "DisplayRenderInterface.h"
#include "RenderIf.h"

#include <string>


DisplayCallback::DisplayCallback(int32_t& rValue,
                    int32_t& rModulation) :
        m_valueBarDrawer(gfxbase::Coord(10, 45),
                         gfxbase::Size2D(76, 13),
                         {0, 255},
                         ColorRGB({255,255,255}),
                         value_utils::Range<ColorRGB>( {0,0,0}, {255, 155, 55}) ),
        m_textField(gfxbase::Coord((96-40)/2, 2),
                    gfxbase::Size2D(40, 34),
                    FreeSansOblique9pt7b,
                    1,
                    {255,255,255},
                    TextField::HPlacement::AlignCenter,
                    TextField::VPlacement::AlignCenter),
        m_rValue(rValue),
        m_rModulation(rModulation)
        {}

void DisplayCallback::revealed(RenderIf& r)
{
    r.setFrameBufRendering(false);
    r.drawRectangle({ gfxbase::Coord(0,0), gfxbase::Size2D(96, 64) }, {0,0,0}, true);
    m_valueBarDrawer.initialDraw();
}

void DisplayCallback::renderDisplays(RenderIf& r)
{
    m_valueBarDrawer.draw(r, m_rValue, m_rModulation);

    std::string txt = "SSD-1331";
    std::string valtxt = std::to_string(m_rValue);

    r.setFrameBufRendering(true);
    //m_textField.drawFieldBorder(r, {255,255,255});
    auto val = m_rValue + m_rModulation;
    uint8_t colCompR = static_cast<uint8_t>(val);
    uint8_t colCompG = static_cast<uint8_t>( (val * 155) / 255 );
    uint8_t colCompB = static_cast<uint8_t>( (val * 55) / 255 );
    ColorRGB txtColor(colCompR, colCompG, colCompB);

    m_textField.setFont(FreeSansOblique9pt7b);
    m_textField.setHPlacement(TextField::HPlacement::AlignCenter);
    m_textField.setVPlacement(TextField::VPlacement::AlignTop);
    m_textField.draw(r, txt, txtColor);

    m_textField.setFont(DefaultMonospace, 2);
    m_textField.setHPlacement(TextField::HPlacement::AlignCenter);
    m_textField.setVPlacement(TextField::VPlacement::AlignBottom);
    m_textField.draw(r, valtxt, {255,255,255});

/*
    m_textField.setHPlacement(TextField::HPlacement::AlignLeft);
    m_textField.setVPlacement(TextField::VPlacement::AlignTop);
    m_textField.draw(r, txt, txtColor);
    m_textField.setHPlacement(TextField::HPlacement::AlignLeft);
    m_textField.setVPlacement(TextField::VPlacement::AlignBottom);
    m_textField.draw(r, txt, txtColor);
    m_textField.setHPlacement(TextField::HPlacement::AlignRight);
    m_textField.setVPlacement(TextField::VPlacement::AlignBottom);
    m_textField.draw(r, txt, txtColor);
    m_textField.setHPlacement(TextField::HPlacement::AlignRight);
    m_textField.setVPlacement(TextField::VPlacement::AlignTop);
    m_textField.draw(r, txt, txtColor);
*/
    r.setFrameBufRendering(false);
}
