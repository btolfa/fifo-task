cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project(server)

set(SOURCES
    Server.cpp
    Server.hpp
)

add_library(server ${SOURCES})
target_link_libraries(server PUBLIC ${Boost_SYSTEM_LIBRARY} spdlog)
target_include_directories(server PUBLIC ${Boost_INCLUDE_DIRS})