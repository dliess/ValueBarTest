#include "HALFpSim.h"
#include "FpInputHandler.h"
#include "FpOutputHandler.h"

#include <iostream>
#include <unistd.h> // usleep()

//#include "CallbackIf_Spec.h"
//#include "Widget_Spec.h"
#include "WidgetTopology_Spec.h"
#include "Vector2D.h"
#include "ValueBarDrawer.h"
#include <cmath>

//#include <thread>

class EncCbHandler : public EncCallback
{
public:
    EncCbHandler(int16_t& encVal) : m_rEncVal(encVal) {}
    virtual void valueChangedCb(const  WidgetTypes::Encoder::ValueType& value, const EncWidget& widget)
    {
        m_rEncVal += value;
        if(m_rEncVal <= 0)
            m_rEncVal = 0;
        if(m_rEncVal > 256)
            m_rEncVal = 256;
        std::cout << "m_rEncVal: " <<  m_rEncVal << std::endl;
        /*std::cout << value << " received from widget ("  <<
         "id: " << widget.id  <<
         " x: " << static_cast<uint32_t>(widget.coord.x) <<
         " y: " << static_cast<uint32_t>(widget.coord.y) << ")" << std::endl;// << widget.toString();*/
    }
private:
    int16_t& m_rEncVal;
};

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

/*
void call_from_thread()
{
    std::cout << "Hello, World" << std::endl;
}
*/

int main()
{
    HALFpSim halGrpc("localhost:50051");
    FpInputHandler<HALFpSim> fpInputs(halGrpc);
    FpOutputHandler fpOutputs;

    int16_t encVal = 50;
    int16_t modVal = 0;

    DisplayWidget dispWidget(WidgetTopology<WidgetTypes::Display>::WidgetId::SSD1331Display, Vec2D(0,0));
    ValueBarDrawer valueBarDrawer(10, 30, 76, 13, 0, 256, {255,255,255}, {55, 0, 0}, {0,0,255}, halGrpc, dispWidget);
    EncCbHandler encCbHandler(encVal);
    DisplayCallback displayCbHandler(valueBarDrawer, encVal, modVal);
    fpInputs.registerEncCb(encCbHandler, EncWidget(EncId::Encoder, Vec2D(Vec2D::ALL, Vec2D::ALL)));
    fpOutputs.registerDisplayCb(displayCbHandler, dispWidget);

  //  std::thread t1(call_from_thread);
    int32_t t = 0;
    uint32_t SleepUs = 20000;
    while(true)
    {
        fpInputs.poll();
        fpOutputs.render();
        usleep(SleepUs);
        t += SleepUs;
        modVal = 30 * sin(6.0*(float)t/1000000.0);
    }


    return 0;
}