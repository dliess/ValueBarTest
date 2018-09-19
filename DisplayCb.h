#ifndef DISPLAY_CB_H
#define DISPLAY_CB_H

#include "CallbackIf_Spec.h"
#include "ValueBarDrawer.h"
#include "DisaplayRenderCbIf.h"

class DisplayCallback : public DisaplayRenderCbIf
{
public:
    DisplayCallback(ValueBarDrawer& valueBarDrawer,
                    ValueDrawer& valueDrawer,
                    int16_t& rValue,
                    int16_t& rModulation) :
        m_rValueBarDrawer(valueBarDrawer),
        m_rValueDrawer(valueDrawer),
        m_rValue(rValue),
        m_rModulation(rModulation),
        m_lastValue(-1)
        {}
    void revealed(const DisplayWidget& widget)
    {
        m_rValueBarDrawer.initialDraw();
    } 
    void render(const DisplayWidget& widget)
    {
        if(m_lastValue != m_rValue)
        {
            m_rValueBarDrawer.draw(m_rValue, m_rModulation);
            m_rValueDrawer.draw(m_rValue);
            m_lastValue = m_rValue;
        }
    }
private:
    ValueBarDrawer& m_rValueBarDrawer;
    ValueDrawer& m_rValueDrawer;
    int16_t& m_rValue;
    int16_t& m_rModulation;
    int16_t  m_lastValue;
};


#endif