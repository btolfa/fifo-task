cmake_minimum_required(VERSION 3.3.1 FATAL_ERROR)

# https://github.com/cppformat/cppformat
project(cppformat)

set(HEADERS
    format.h
)

set(SOURCES
    format.cc
    ${HEADERS}
)

add_library(cppformat ${SOURCES})
target_include_directories(cppformat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET cppformat PROPERTY CXX_STANDARD 14)
set_property(TARGET cppformat PROPERTY CXX_STANDARD_REQUIRED ON)

add_library(cppformat::cppformat ALIAS cppformat)