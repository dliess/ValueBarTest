#ifndef ENC_CALLBACKS_H
#define ENC_CALLBACKS_H

#include "ValueUtils.h"
#include "CallbackIf_Spec.h"
#include "FpInputHandler.h"
#include "HALFpSim.h"
#include "FpWidgetIn_Spec.h"
#include <cstdint>

class EncCbHandler : public EncCallback
{
public:
    EncCbHandler(FpInputHandler<HALFpSim>& rFpInputHandler,
                 int32_t& rEncVal,
                 int32_t& rModAmplitude,
                 int32_t& rModFrequencyHz) :
        m_rFpInputHandler(rFpInputHandler),
        m_rEncVal(rEncVal),
        m_rModAmplitude(rModAmplitude),
        m_rModFrequencyHz(rModFrequencyHz)
        {}
    virtual void valueChangedCb(const  fpw::Encoder::ValueType& incr, const EncWidget& widget)
    {
        switch(widget.coord.x)
        {
            case 0:
                if( fpw::Button::ValueType::Released == m_rFpInputHandler.btnValue(BtnWidget(fpw::Button::Encoder, Vec2D(0,0))) )
                {
                    m_rEncVal += incr;
                    value_utils::limitToRange(m_rEncVal, {0, 255});
                }
                break;
            case 1:
                if( fpw::Button::ValueType::Released == m_rFpInputHandler.btnValue(BtnWidget(fpw::Button::Encoder, Vec2D(1,0))) )
                {
                    m_rModAmplitude += incr;
                    value_utils::limitToRange(m_rModAmplitude, {0, 50});
                }
                else
                {
                    m_rModFrequencyHz += incr;
                    value_utils::limitToRange(m_rModFrequencyHz, {0, 5000});
                }
                break;
        } 
    }
private:
    FpInputHandler<HALFpSim>& m_rFpInputHandler;
    int32_t& m_rEncVal;
    int32_t& m_rModAmplitude;
    int32_t& m_rModFrequencyHz;
};

#endif