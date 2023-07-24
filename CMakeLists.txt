cmake_minimum_required(VERSION 3.10) # specify the minimum version for CMake

project(ChipControl C) # name of your project and the language

set(CMAKE_C_STANDARD 99) # set the C standard

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

enable_testing() # This turns on CTest.
add_subdirectory(src)
add_subdirectory(test)
