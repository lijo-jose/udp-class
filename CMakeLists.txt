cmake_minimum_required(VERSION 3.0.0)
project(abc VERSION 0.1.0)

include_directories(inc)
set(SOURCE_FILES test/test_udp_comm.cpp src/udp_class.cpp)
add_executable(test_comm ${SOURCE_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
