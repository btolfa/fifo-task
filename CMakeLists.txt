cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(fifo_task CXX)

option(BUILD_TESTS "Build tests" ON)

# Собираем с флагами для c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_BUILD_TYPE EQUAL "Debug")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wnon-virtual-dtor -Wshadow -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -pedantic")
endif()

find_package(Boost 1.58 REQUIRED COMPONENTS filesystem system)
find_package(Threads)

add_subdirectory(libs/cppformat)
add_subdirectory(libs/cxxopts)
add_subdirectory(libs/spdlog)

add_subdirectory(src/server)
add_subdirectory(src/led)
add_subdirectory(src/session)
add_subdirectory(src/command)

set(SOURCE_FILES
        src/main/main.cpp
)

add_executable(fifoserver ${SOURCE_FILES})
target_link_libraries(fifoserver
        cxxopts::cxxopts
        spdlog
        ${Boost_LIBRARIES}
        Threads::Threads

        server
)
target_include_directories(fifoserver PUBLIC ${Boost_INCLUDE_DIRS})

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()