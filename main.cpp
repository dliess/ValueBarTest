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
#include "EncCallbacks.h"
#include "DisplayCb.h"

int main()
{
    HALFpSim halGrpc("localhost:50051");
    FpInputHandler<HALFpSim> fpInputs(halGrpc);
    FpOutputHandler fpOutputs;

    int16_t  encVal = 50;
    int16_t  modVal = 0;
    int16_t modAmplitude = 0;
    int16_t modFrequencyHz = 1;

    DisplayWidget dispWidget(WidgetTopology<WidgetTypes::Display>::WidgetId::SSD1331Display, Vec2D(0,0));
    ValueBarDrawer valueBarDrawer(10, 30, 76, 13, 0, 256, {255,255,255}, {55, 0, 0}, {0,0,255}, halGrpc, dispWidget);
    EncCbHandler encCbHandler(fpInputs, encVal, modAmplitude, modFrequencyHz);

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
        modVal = modAmplitude * sin(((float)modFrequencyHz/100.0)*(float)t/1000000.0);
    }


    return 0;
}