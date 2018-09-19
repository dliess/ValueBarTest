#ifndef ENC_CALLBACKS_H
#define ENC_CALLBACKS_H

#include "utils.h"
#include "CallbackIf_Spec.h"
#include "FpInputHandler.h"
#include "HALFpSim.h"
#include <cstdint>

class EncCbHandler : public EncCallback
{
public:
    EncCbHandler(FpInputHandler<HALFpSim>& rFpInputHandler,
                 int16_t& rEncVal,
                 int16_t& rModAmplitude,
                 int16_t& rModFrequencyHz) :
        m_rFpInputHandler(rFpInputHandler),
        m_rEncVal(rEncVal),
        m_rModAmplitude(rModAmplitude),
        m_rModFrequencyHz(rModFrequencyHz)
        {}
    virtual void valueChangedCb(const  WidgetTypes::Encoder::ValueType& incr, const EncWidget& widget)
    {
        switch(widget.coord.x)
        {
            case 0:
                if( BtnValue::Released == m_rFpInputHandler.btnValue(BtnWidget(BtnId::Encoder, Vec2D(0,0))) )
                {
                    m_rEncVal += incr;
                    stayInRange<int16_t>(m_rEncVal, 0, 255);
                }
                break;
            case 1:
                if( BtnValue::Released == m_rFpInputHandler.btnValue(BtnWidget(BtnId::Encoder, Vec2D(1,0))) )
                {
                    m_rModAmplitude += incr;
                    stayInRange<int16_t>(m_rModAmplitude, 0, 50);
                }
                else
                {
                    m_rModFrequencyHz += incr;
                    stayInRange<int16_t>(m_rModFrequencyHz, 0, 5000);
                }
                break;
        } 
    }
private:
    FpInputHandler<HALFpSim>& m_rFpInputHandler;
    int16_t& m_rEncVal;
    int16_t& m_rModAmplitude;
    int16_t& m_rModFrequencyHz;
};

#endif