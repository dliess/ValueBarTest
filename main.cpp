#include "HALFpSim.h"
#include "FpInputHandler.h"
#include "FpOutputHandler.h"


int main()
{
    HALFpSim hal;
    FpInputHandler<HALFpSim> fpInputs(hal);
    FpInputOutput fpOutputs;
    return 0;
}