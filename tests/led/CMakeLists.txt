cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project(led-test)

add_executable(led-test
        LedDriverTest.cpp
        MockLedDriver.hpp)
target_link_libraries(led-test
    led
    gtest
    gmock
    gmock_main
)

add_test(NAME LedDriverTest COMMAND led-test)