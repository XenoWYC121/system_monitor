cmake_minimum_required(VERSION 3.20)
project(system_monitor)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

include(CTest)

enable_testing()

add_subdirectory(test)