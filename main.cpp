#include "HALFpSim.h"
#include "FpInputHandler.h"
#include "FpOutputHandler.h"
#include "CallbackIf_Spec.h"
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
    FpOutputHandler<HALFpSim> fpOutputs(halGrpc);

    int16_t encVal = 50;
    int16_t modVal = 0;
    int16_t modAmplitude = 0;
    int16_t modFrequencyHz = 1;

    DisplayWidget dispWidget(fpw::Display::Id::SSD1331Display, Vec2D(0,0));
    ValueBarDrawer valueBarDrawer(10, 30, 76, 13, 0, 256, {255,255,255}, {55, 55, 55}, {0,0,255}, halGrpc, dispWidget);
    TextField textField(halGrpc,
                        dispWidget,
                        fpw::Display::Coord(30, 2),
                        fpw::Display::Size2D(40, 20),
                        fpw::Display::FontId::FreeMonoBold,
                        fpw::Display::FontSize::Pix18,
                        {255,255,255},
                        TextField::HPlacement::AlignCenter,
                        TextField::VPlacement::AlignCenter);
    EncCbHandler encCbHandler(fpInputs, encVal, modAmplitude, modFrequencyHz);

    DisplayCallback displayCbHandler(valueBarDrawer, textField, encVal, modVal);
    EncWidget encWidget(fpw::Encoder::Id::Encoder, Vec2D(Vec2D::ALL, Vec2D::ALL));
    fpInputs.registerEncCb(encCbHandler, encWidget);
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