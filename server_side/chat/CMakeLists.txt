cmake_minimum_required(VERSION 3.14)

project(chat)

set(CMAXE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/chat.cpp")
set(HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/chat.hpp")

set(CHAT_LIB "${PROJECT_NAME}_lib")
set(CHAT_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(CHAT_LIB ${CHAT_LIB} PARENT_SCOPE)
set(CHAT_SOURCES_HEADERS_LIB ${SOURCES} ${HEADERS} PARENT_SCOPE)
set(CHAT_INCLUDE_DIRS ${CHAT_INCLUDE_DIRS} PARENT_SCOPE)

add_library(${CHAT_LIB} ${SOURCES} ${HEADERS})
target_include_directories(${CHAT_LIB} PUBLIC ${CHAT_INCLUDE_DIRS})

if(BUILD_TESTS OR BUILD_ALL)
    enable_testing()
    add_subdirectory(tests_chat)    
endif()
