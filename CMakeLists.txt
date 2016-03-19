cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(fifo_task CXX)

option(BUILD_TESTS "Build tests" ON)

# Собираем с флагами для c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.58 REQUIRED COMPONENTS filesystem)

add_subdirectory(libs/cppformat)
add_subdirectory(libs/cxxopts)
add_subdirectory(libs/spdlog)

set(SOURCE_FILES
        src/main/main.cpp
)

add_executable(fifoserver ${SOURCE_FILES})
target_link_libraries(fifoserver cppformat::cppformat cxxopts::cxxopts spdlog ${Boost_LIBRARIES})
target_include_directories(fifoserver PUBLIC ${Boost_INCLUDE_DIRS})

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()