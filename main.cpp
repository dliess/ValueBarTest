#include "HALFpSim.h"
#include "FpInputHandler.h"
#include "FpOutputHandler.h"


int main()
{
    HALFpSim halGrpc("localhost:50051");
    FpInputHandler<HALFpSim> fpInputs(halGrpc);
    FpOutputHandler fpOutputs;
    return 0;
}