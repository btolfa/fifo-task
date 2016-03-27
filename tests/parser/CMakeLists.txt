cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project(parser-test)

add_executable(parser-test
        ParserTest.cpp)

target_link_libraries(parser-test
    command

    gtest
    gmock
    gmock_main
)
target_include_directories(parser-test PUBLIC ${Boost_INCLUDE_DIRS})

add_test(NAME ParserTest COMMAND parser-test)