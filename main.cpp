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

    EncCbHandler encCbHandler(fpInputs, encVal, modAmplitude, modFrequencyHz);
    DisplayCallback displayCbHandler(encVal, modVal);
    fpInputs.registerEncCb(encCbHandler, EncWidget(fpw::Encoder::Id::Encoder, Vec2D::ALL, Vec2D::ALL));
    fpOutputs.registerDisplayCb(displayCbHandler, DisplayWidget(fpw::Display::Id::SSD1331Display));

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