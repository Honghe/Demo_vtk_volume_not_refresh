cmake_minimum_required(VERSION 3.6)
project(Demo_vtk_volume_not_refresh)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(VTK REQUIRED
        )
include(${VTK_USE_FILE})

set(SOURCE_FILES
        main.cpp
        ViewPort1.cpp
        MyDirector.cpp
        jet256colormap.cpp
        TimerCallback.cpp)

set(name "Demo_vtk_volume_not_refresh")
add_executable(${name} ${SOURCE_FILES})
target_link_libraries(${name} ${VTK_LIBRARIES})
