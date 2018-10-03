#ifndef DISPLAY_CB_H
#define DISPLAY_CB_H

#include "CallbackIf_Spec.h"
#include "ValueBarDrawer.h"
#include "DisaplayRenderCbIf.h"
#include "DefaultMonospace.h"
#include "FreeMono9pt7b.h"
#include "FreeSansOblique9pt7b.h"

#include <string>


class DisplayCallback : public DisaplayRenderCbIf
{
public:
    DisplayCallback(int32_t& rValue,
                    int32_t& rModulation) :
        m_valueBarDrawer(fpw::Display::Coord(10, 45),
                         fpw::Display::Size2D(76, 13),
                         {0, 255},
                         fpw::Display::ColorRGB({255,255,255}),
                         value_utils::Range<fpw::Display::ColorRGB>( {0,0,0}, {255, 155, 55}) ),
        m_textField(fpw::Display::Coord((96-40)/2, 2),
                    fpw::Display::Size2D(40, 34),
                    FreeSansOblique9pt7b,
                    1,
                    {255,255,255},
                    TextField::HPlacement::AlignCenter,
                    TextField::VPlacement::AlignCenter),
        m_rValue(rValue),
        m_rModulation(rModulation)
        {}
    void revealed(DisplayInterface& displayInterface)
    {
        displayInterface.setFrameBufRendering(false);
        displayInterface.drawRectangle({ fpw::Display::Coord(0,0), fpw::Display::Size2D(96, 64) }, {0,0,0}, true);
        m_valueBarDrawer.initialDraw();
    } 
    void renderDisplays(DisplayInterface& displayInterface)
    {
        m_valueBarDrawer.draw(displayInterface, m_rValue, m_rModulation);

        std::string txt = "SSD-1331";
        std::string valtxt = std::to_string(m_rValue);

        displayInterface.setFrameBufRendering(true);
        //m_textField.drawFieldBorder(displayInterface, {255,255,255});
        auto val = m_rValue + m_rModulation;
        uint8_t colCompR = static_cast<uint8_t>(val);
        uint8_t colCompG = static_cast<uint8_t>( (val * 155) / 255 );
        uint8_t colCompB = static_cast<uint8_t>( (val * 55) / 255 );
        fpw::Display::ColorRGB txtColor(colCompR, colCompG, colCompB);

        m_textField.setFont(FreeSansOblique9pt7b);
        m_textField.setHPlacement(TextField::HPlacement::AlignCenter);
        m_textField.setVPlacement(TextField::VPlacement::AlignTop);
        m_textField.draw(displayInterface, txt, txtColor);

        m_textField.setFont(DefaultMonospace, 2);
        m_textField.setHPlacement(TextField::HPlacement::AlignCenter);
        m_textField.setVPlacement(TextField::VPlacement::AlignBottom);
        m_textField.draw(displayInterface, valtxt, {255,255,255});

/*
        m_textField.setHPlacement(TextField::HPlacement::AlignLeft);
        m_textField.setVPlacement(TextField::VPlacement::AlignTop);
        m_textField.draw(displayInterface, txt, txtColor);
        m_textField.setHPlacement(TextField::HPlacement::AlignLeft);
        m_textField.setVPlacement(TextField::VPlacement::AlignBottom);
        m_textField.draw(displayInterface, txt, txtColor);
        m_textField.setHPlacement(TextField::HPlacement::AlignRight);
        m_textField.setVPlacement(TextField::VPlacement::AlignBottom);
        m_textField.draw(displayInterface, txt, txtColor);
        m_textField.setHPlacement(TextField::HPlacement::AlignRight);
        m_textField.setVPlacement(TextField::VPlacement::AlignTop);
        m_textField.draw(displayInterface, txt, txtColor);
*/
        displayInterface.setFrameBufRendering(false);
    }
private:
    ValueBarDrawer  m_valueBarDrawer;
    TextField       m_textField;
    int32_t&        m_rValue;
    int32_t&        m_rModulation;
};


#endif