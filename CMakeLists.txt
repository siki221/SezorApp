cmake_minimum_required(VERSION 3.0)
project(fleXdSimulator VERSION "0.0.1")
set(PROJECT_DESCRIPTION "FleX-d Simulation of Senzors")

message(STATUS "***" )
message(STATUS "* " ${PROJECT_NAME})
message(STATUS "***")

set_property(
    CACHE
    CMAKE_BUILD_TYPE
    PROPERTY STRINGS
    "Debug"
    "Release"
)

#add_subdirectory(SenzorSimulator)
add_subdirectory(SenzorReader)

