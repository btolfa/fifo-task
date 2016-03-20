cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project(session-test)

add_executable(session-test
        SessionTest.cpp)

target_link_libraries(session-test
    session

    gtest
    gmock
    gmock_main
)
target_include_directories(session-test PUBLIC ${Boost_INCLUDE_DIRS})

add_test(NAME SessionTest COMMAND session-test)