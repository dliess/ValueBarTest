cmake_minimum_required(VERSION 2.6)

set (CMAKE_CXX_STANDARD 11)

project(ValueBarTest C CXX)

add_subdirectory(FrontPanelIO/c++)

add_executable(valueBarTest
    main.cpp
    ValueBarDrawer.cpp
    ValueDrawer.cpp)
target_link_libraries(valueBarTest 
    HALFpSim
    FPIOHandler
)