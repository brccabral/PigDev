cmake_minimum_required(VERSION 3.27)
project(PigDev)

add_subdirectory(pig)

option(BUILD_EXAMPLE "Build example, must install pig first." OFF)

if(BUILD_EXAMPLE)
find_package(pig REQUIRED)
add_subdirectory(example)
endif()
