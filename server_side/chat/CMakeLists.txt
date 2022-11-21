cmake_minimum_required(VERSION 3.14)

project(chat)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES ./src/chat.cpp)
set(HEADERS ./include/chat.hpp)

set(CHAT_LIB ${CHAT_LIB} PARENT_SCOPE)
set(CHAT_INCLUDE_DIRS ${CHAT_INCLUDE_DIRS} PARENT_SCOPE)

set(LIB_NAME ${PROJECT_NAME}_LIB)

add_library(${LIB_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${LIB_NAME} PUBLIC ./include)

set(CHAT_LIB ${LIB_NAME})
set(CHAT_INCLUDE_DIRS ${LIB_NAME} ./include)

set(CHAT_LIB ${Project_LIB} PARENT_SCOPE)
set(CHAT_INCLUDE_DIRS ${Project_INCLUDE_DIRS} PARENT_SCOPE)
