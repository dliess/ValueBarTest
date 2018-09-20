#include "HALFpSim.h"
#include "FpInputHandler.h"
#include "FpOutputHandler.h"
#include "CallbackIf_Spec.h"
#include "WidgetTopology_Spec.h"
#include "Vector2D.h"
#include "ValueBarDrawer.h"
#include "TextField.h"
#include "EncCallbacks.h"
#include "DisplayCb.h"

#include <iostream>
#include <unistd.h> // usleep()
#include <cmath>

int main()
{
    HALFpSim halGrpc("localhost:50051");
    FpInputHandler<HALFpSim> fpInputs(halGrpc);
    FpOutputHandler fpOutputs;

    int16_t encVal = 50;
    int16_t modVal = 0;
    int16_t modAmplitude = 0;
    int16_t modFrequencyHz = 1;

    DisplayWidget dispWidget(WidgetTopology<WidgetTypes::Display>::WidgetId::SSD1331Display, Vec2D(0,0));
    ValueBarDrawer valueBarDrawer(10, 30, 76, 13, 0, 256, {255,255,255}, {55, 55, 55}, {0,0,255}, halGrpc, dispWidget);
    TextField textField(halGrpc,
                        dispWidget,
                        WidgetTypes::Display::Coord(30, 2),
                        WidgetTypes::Display::Size2D(40, 20),
                        WidgetTypes::Display::FontId::FreeMonoBold,
                        WidgetTypes::Display::FontSize::Pix18,
                        {255,255,255},
                        TextField::HPlacement::AlignCenter,
                        TextField::VPlacement::AlignCenter);
    EncCbHandler encCbHandler(fpInputs, encVal, modAmplitude, modFrequencyHz);

    DisplayCallback displayCbHandler(valueBarDrawer, textField, encVal, modVal);
    fpInputs.registerEncCb(encCbHandler, EncWidget(EncId::Encoder, Vec2D(Vec2D::ALL, Vec2D::ALL)));
    fpOutputs.registerDisplayCb(displayCbHandler, dispWidget);

  //  std::thread t1(call_from_thread);
    int32_t t = 0;
    const uint32_t SleepUs = 20000;
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