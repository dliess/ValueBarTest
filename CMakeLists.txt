cmake_minimum_required(VERSION 2.6)

set (CMAKE_CXX_STANDARD 11)

project(ValueBarTest C CXX)

add_subdirectory(FrontPanelIO)
add_subdirectory(GraphicWidgets)


add_executable(valueBarTest
    EncCallbacks.cpp
    DisplayCb.cpp
    main.cpp
)

target_link_libraries(valueBarTest 
    HALFpSim
    FpInputHandler
    GraphicWidgets
)