cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project(server-test)

add_executable(server-test
        ServerTest.cpp
        ../../src/server/Server.hpp
        ../../src/server/Server.cpp
)
target_link_libraries(server-test gtest gmock gmock_main ${Boost_LIBRARIES})
target_include_directories(server-test PUBLIC ${Boost_INCLUDE_DIRS})

add_test(NAME ServerTest COMMAND server-test)