#ifndef DISPLAY_CB_H
#define DISPLAY_CB_H

#include "CallbackIf_Spec.h"
#include "ValueBarDrawer.h"
#include "DisaplayRenderCbIf.h"

class DisplayCallback : public DisaplayRenderCbIf
{
public:
    DisplayCallback(int32_t& rValue,
                    int32_t& rModulation) :
        m_valueBarDrawer(fpw::Display::Coord(10, 30),
                         fpw::Display::Size2D(76, 13),
                         {0, 255},
                         fpw::Display::ColorRGB({255,255,255}),
                         value_utils::Range<fpw::Display::ColorRGB>( {0,0,0}, {255, 155, 55}) ),
        m_textField(fpw::Display::Coord(30, 2),
                    fpw::Display::Size2D(40, 20),
                    fpw::Display::FontId::FreeMonoBold,
                    fpw::Display::FontSize::Pix18,
                    {255,255,255},
                    TextField::HPlacement::AlignCenter,
                    TextField::VPlacement::AlignCenter),
        m_rValue(rValue),
        m_rModulation(rModulation),
        m_lastValue(-1)
        {}
    void revealed(DisplayInterface& displayInterface)
    {
        m_valueBarDrawer.initialDraw();
        displayInterface.setBypass(false);
        m_textField.clear(displayInterface);
        m_textField.drawFieldBorder(displayInterface, {255,255,255});
        displayInterface.setBypass(true);
    } 
    void render(DisplayInterface& displayInterface)
    {
        m_valueBarDrawer.draw(displayInterface, m_rValue, m_rModulation);
        if(m_lastValue != m_rValue)
        {
            m_textField.draw(displayInterface, m_rValue, {100, 0, static_cast<uint8_t>(m_rValue)});
            m_lastValue = m_rValue;
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