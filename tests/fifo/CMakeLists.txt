cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project(fifo-test)

add_executable(fifo-test FifoTest.cpp)
target_link_libraries(fifo-test gtest gmock gmock_main ${Boost_LIBRARIES})
target_include_directories(fifo-test PUBLIC ${Boost_INCLUDE_DIRS})

add_test(NAME FifoTest COMMAND fifo-test)