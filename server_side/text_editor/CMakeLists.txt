cmake_minimum_required(VERSION 3.14)

project(text_editor)

set(CMAXE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES "src/line.cpp")
set(HEADERS "include/line.hpp")

set(FOR_TEST_LIB "${PROJECT_NAME}_lib")
set(FOR_TEST_INCLUDE_DIRS "/include")

add_library(${PROJECT_NAME}_lib STATIC ${SOURCES} ${HEADERS})
target_include_directories(${FOR_TEST_LIB} PUBLIC ${FOR_TEST_INCLUDE_DIRS})

if(BUILD_TESTS OR BUILD_ALL)
    enable_testing()
    add_subdirectory(tests_text_editor)    
endif()
