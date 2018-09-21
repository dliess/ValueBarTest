#ifndef DISPLAY_CB_H
#define DISPLAY_CB_H

#include "CallbackIf_Spec.h"
#include "ValueBarDrawer.h"
#include "DisaplayRenderCbIf.h"

class DisplayCallback : public DisaplayRenderCbIf
{
public:
    DisplayCallback(int16_t& rValue,
                    int16_t& rModulation) :
        m_valueBarDrawer(10, 30, 76, 13, 0, 256, {255,255,255}, {55, 55, 55}, {0,0,255}),
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
        m_textField.clear(displayInterface);
        m_textField.drawFieldBorder(displayInterface, {255,255,255});
    } 
    void render(DisplayInterface& displayInterface)
    {
        m_valueBarDrawer.draw(displayInterface, m_rValue, m_rModulation);
        m_textField.draw(displayInterface, m_rValue, {100, 0, static_cast<uint8_t>(m_rValue)});
        m_lastValue = m_rValue;
    }
private:
    ValueBarDrawer  m_valueBarDrawer;
    TextField       m_textField;
    int16_t&        m_rValue;
    int16_t&        m_rModulation;
    int16_t         m_lastValue;
};


#endif