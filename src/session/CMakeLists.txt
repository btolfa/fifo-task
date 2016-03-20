cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project(session)

set(SOURCES
    SessionFactory.hpp
    Session.cpp
    Session.hpp
)

add_library(session ${SOURCES})
target_link_libraries(session PUBLIC ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
target_include_directories(session PUBLIC ${Boost_INCLUDE_DIRS})