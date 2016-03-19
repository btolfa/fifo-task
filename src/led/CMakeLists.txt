cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project(led)

set(SOURCES
    LedDriver.hpp
    LedDriverImpl.hpp
    LedDriverImpl.cpp
)

add_library(led ${SOURCES})
target_link_libraries(led PUBLIC spdlog)