cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME "server")

set(CMAKE_CXX_STANDARD 17)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp)
set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/server.hpp)

project(${PROJECT_NAME})
