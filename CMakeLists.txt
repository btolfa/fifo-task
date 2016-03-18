cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
project(fifo_task CXX)

# Собираем с флагами для c++11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SOURCE_FILES main.cpp)
add_executable(fifo_task ${SOURCE_FILES})