#include "HALFpSim.h"
#include "FpInputHandler.h"
#include "FpOutputHandler.h"

#include <iostream>
#include <unistd.h> // usleep()

//#include "CallbackIf_Spec.h"
//#include "Widget_Spec.h"
#include "WidgetTopology_Spec.h"
#include "Vector2D.h"

//#include <thread>

class EncCbHandler : public EncCallback
{
public:
    virtual void valueChangedCb(const  WidgetTypes::Encoder::ValueType& value, const EncWidget& widget)
    {
        std::cout << value << " received from widget" << std::endl;// << widget.toString();
    }
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

    EncCbHandler encCbHandler;
    fpInputs.registerEncCb(encCbHandler, EncWidget(EncId::Encoder, Vec2D(Vec2D::ALL, Vec2D::ALL)));


  //  std::thread t1(call_from_thread);

    while(true)
    {
        fpInputs.poll();
        usleep(10000);
    }


    return 0;
}