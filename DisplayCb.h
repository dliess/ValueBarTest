#ifndef DISPLAY_CB_H
#define DISPLAY_CB_H

#include "CallbackIf_Spec.h"
#include "ValueBarDrawer.h"
#include "DisaplayRenderCbIf.h"
#include "DefaultMonospace.h"
#include "FreeMono9pt7b.h"

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
        m_textField(fpw::Display::Coord(30, 2),
                    fpw::Display::Size2D(40, 34),
                    DefaultMonospace,
                    {255,255,255},
                    TextField::HPlacement::AlignCenter,
                    TextField::VPlacement::AlignCenter),
        m_rValue(rValue),
        m_rModulation(rModulation),
        m_lastValue(-1)
        {}
    void revealed(DisplayInterface& displayInterface)
    {
        displayInterface.setFrameBufRendering(false);
        displayInterface.drawRectangle({ fpw::Display::Coord(0,0), fpw::Display::Size2D(96, 64) }, {0,0,0}, true);
        m_valueBarDrawer.initialDraw();
        //m_textField.clear(displayInterface);
        //displayInterface.setFrameBufRendering(false);
        m_textField.drawFieldBorder(displayInterface, {255,255,255});
        //displayInterface.setFrameBufRendering(true);
    } 
    void render(DisplayInterface& displayInterface)
    {
        m_valueBarDrawer.draw(displayInterface, m_rValue, m_rModulation);

        if(m_lastValue != m_rValue)
        {
            displayInterface.setFrameBufRendering(true);
            m_textField.drawFieldBorder(displayInterface, {255,255,255});
            m_textField.draw(displayInterface, m_rValue, {100, 0, static_cast<uint8_t>(m_rValue)});
            m_lastValue = m_rValue;
            displayInterface.setFrameBufRendering(false);
        }
    }
private:
    ValueBarDrawer  m_valueBarDrawer;
    TextField       m_textField;
    int32_t&        m_rValue;
    int32_t&        m_rModulation;
    int32_t         m_lastValue;
};


#endif