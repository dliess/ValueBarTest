#include "EncCallbacks.h"

EncCbHandler::EncCbHandler(FpInputHandler<HALFpSim>& rFpInputHandler,
                int32_t& rEncVal,
                int32_t& rModAmplitude,
                int32_t& rModFrequencyHz) :
    m_rFpInputHandler(rFpInputHandler),
    m_rEncVal(rEncVal),
    m_rModAmplitude(rModAmplitude),
    m_rModFrequencyHz(rModFrequencyHz)
    {}
    
void EncCbHandler::valueChangedCb(const  fpw::Encoder::ValueType& incr, const EncWidget& widget)
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