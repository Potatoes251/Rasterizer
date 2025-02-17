cmake_minimum_required(VERSION 3.30.1)

project(Rasterizer)

set(CMAKE_CXX_STANDARD 11)				
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EXE_NAME Rasterizer)

add_subdirectory(LibMath)
add_subdirectory(Rasterizer)


if(MSVC)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${EXE_NAME})
endif()