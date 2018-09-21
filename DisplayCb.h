#ifndef DISPLAY_CB_H
#define DISPLAY_CB_H

#include "CallbackIf_Spec.h"
#include "ValueBarDrawer.h"
#include "DisaplayRenderCbIf.h"

class DisplayCallback : public DisaplayRenderCbIf
{
public:
    DisplayCallback(ValueBarDrawer& valueBarDrawer,
                    TextField& textField,
                    int16_t& rValue,
                    int16_t& rModulation) :
        m_rValueBarDrawer(valueBarDrawer),
        m_rTextField(textField),
        m_rValue(rValue),
        m_rModulation(rModulation),
        m_lastValue(-1)
        {}
    void revealed(const DisplayWidget& widget)
    {
        m_rValueBarDrawer.initialDraw();
        m_rTextField.clear();
        m_rTextField.drawFieldBorder({255,255,255});
    } 
    void render(DisplayInterface& displayInterface)
    {
        m_rValueBarDrawer.draw(m_rValue, m_rModulation);
        m_rTextField.draw(m_rValue, {100, 0, static_cast<uint8_t>(m_rValue)});
        m_lastValue = m_rValue;
    }
private:
    ValueBarDrawer& m_rValueBarDrawer;
    TextField& m_rTextField;
    int16_t& m_rValue;
    int16_t& m_rModulation;
    int16_t  m_lastValue;
};


#endif