#ifndef DISPLAY_CB_H
#define DISPLAY_CB_H

#include "CallbackIf_Spec.h"
#include "ValueBarDrawer.h"
#include "DisaplayRenderCbIf.h"

class DisplayCallback : public DisaplayRenderCbIf
{
public:
    DisplayCallback(ValueBarDrawer& valueBarDrawer,
                    int16_t& rValue,
                    int16_t& rModulation) :
        m_rValueBarDrawer(valueBarDrawer),
        m_rValue(rValue),
        m_rModulation(rModulation)
        {}
    void revealed(const DisplayWidget& widget)
    {
        m_rValueBarDrawer.initialDraw();
    } 
    void render(const DisplayWidget& widget)
    {
        m_rValueBarDrawer.draw(m_rValue, m_rModulation);
    }
private:
    ValueBarDrawer& m_rValueBarDrawer;
    int16_t& m_rValue;
    int16_t& m_rModulation;
};


#endif