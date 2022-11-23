cmake_minimum_required(VERSION 3.14)

project(server)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES "src/server.cpp")
set(HEADERS "include/server.hpp")

message("SOURCES " ${SOURCES})
message("HEADERS " ${HEADERS})

set(SERVER_LIB ${PROJECT_NAME}_LIB)
set(SERVER_INCLUDE_DIRS ${PROJECT_NAME}_INCLUDE_DIRS)

add_library(${SERVER_LIB} ${SOURCES} ${HEADERS})
target_include_directories(${SERVER_LIB} PUBLIC ./include)

set(SERVER_LIB ${SERVER_LIB} PARENT_SCOPE)
set(SERVER_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
