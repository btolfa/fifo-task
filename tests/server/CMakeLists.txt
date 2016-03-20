cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project(server-test)

add_executable(server-test
        ServerTest.cpp)

target_link_libraries(server-test
    server
    ${Boost_LIBRARIES}
    spdlog

    gtest
    gmock
    gmock_main
)

add_test(NAME ServerTest COMMAND server-test)