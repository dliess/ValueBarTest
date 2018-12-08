#ifndef DISPLAY_CB_H
#define DISPLAY_CB_H

#include "DisaplayRenderCbIf.h"
#include "ValueBarDrawer.h"
#include "TextField.h"

class DisplayCallback : public DisaplayRenderCbIf
{
public:
    DisplayCallback(int32_t& rValue,
                    int32_t& rModulation);
    void revealed(RenderIf& r);
    void renderDisplays(RenderIf& r);

private:
    ValueBarDrawer  m_valueBarDrawer;
    TextField       m_textField;
    int32_t&        m_rValue;
    int32_t&        m_rModulation;
};


#endif