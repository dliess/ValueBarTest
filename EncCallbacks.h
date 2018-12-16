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
    EncCbHandler(FpInputHandler& rFpInputHandler,
                 int32_t& rEncVal,
                 int32_t& rModAmplitude,
                 int32_t& rModFrequencyHz);
    virtual void valueChangedCb(const  fpw::Encoder::ValueType& incr, const EncWidget& widget);
private:
    FpInputHandler& m_rFpInputHandler;
    int32_t& m_rEncVal;
    int32_t& m_rModAmplitude;
    int32_t& m_rModFrequencyHz;
};

#endif