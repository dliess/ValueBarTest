cmake_minimum_required(VERSION 2.6)

set (CMAKE_CXX_STANDARD 11)

project(ValueBarTest C CXX)

add_subdirectory(FrontPanelIO/c++)

add_executable(valueBarTest main.cpp)
target_link_libraries(valueBarTest 
    HALFpSim
    FPIOHandler
    "-lgrpc++"
    "-lgrpc_unsecure"
    "-lgpr"
    "-lcares"
    "-lz"
    "-lprotobuf"
    "-lpthread"
    "-laddress_sorting"
)

# it was building with this linker command:
#/usr/bin/c++ -rdynamic CMakeFiles/valueBarTest.dir/main.cpp.o  -o valueBarTest FrontPanelIO/c++/HAL/libHALFpSim.a FrontPanelIO/c++/FrontPanelIO/libFPIOHandler.a -lFpSimGrpc -lgrpc++ -lgrpc_unsecure -lgpr -lcares -lz -lprotobuf -lpthread -laddress_sorting