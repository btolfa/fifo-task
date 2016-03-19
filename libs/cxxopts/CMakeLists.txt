cmake_minimum_required(VERSION 3.3.1 FATAL_ERROR)

# https://github.com/jarro2783/cxxopts
project(cxxopts)

add_library(cxxopts INTERFACE)
target_include_directories(cxxopts INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(cxxopts::cxxopts ALIAS cxxopts)