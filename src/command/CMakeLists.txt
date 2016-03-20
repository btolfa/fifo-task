cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project(command)

set(SOURCES
        Command.hpp Parser.hpp)

add_library(command ${SOURCES})
target_link_libraries(command PUBLIC spdlog)
target_include_directories(command PUBLIC ${Boost_INCLUDE_DIRS})