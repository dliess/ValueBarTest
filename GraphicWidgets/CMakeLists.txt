cmake_minimum_required(VERSION 2.6)

set (CMAKE_CXX_STANDARD 11)

add_library(GraphicWidgets
    STATIC
        "ValueBarDrawer.cpp"
        "TextField.cpp"
)

target_include_directories(GraphicWidgets PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(GraphicWidgets FpDisplayHandler)