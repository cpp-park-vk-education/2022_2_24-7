cmake_minimum_required(VERSION 3.14)

project(server)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES ./src/server.cpp)
set(HEADERS ./include/server.hpp)

set(SERVER_LIB ${SERVER_LIB} PARENT_SCOPE)
set(SERVER_INCLUDE_DIRS ${SERVER_INCLUDE_DIRS} PARENT_SCOPE)

set(LIB_NAME ${PROJECT_NAME}_LIB)

add_library(${LIB_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${LIB_NAME} PUBLIC ./include)

set(SERVER_LIB ${LIB_NAME})
set(SERVER_INCLUDE_DIRS ${LIB_NAME} ./include)

set(SERVER_LIB ${Project_LIB} PARENT_SCOPE)
set(SERVER_INCLUDE_DIRS ${Project_INCLUDE_DIRS} PARENT_SCOPE)
