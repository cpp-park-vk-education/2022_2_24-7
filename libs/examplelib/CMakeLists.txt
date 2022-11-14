cmake_minimum_required(VERSION 3.14)

project("ExampleLib")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -Wpedantic -Werror")

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/project.cpp)
set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/project.hpp)

set(LIB_NAME ${PROJECT_NAME}_LIB)

add_library(${LIB_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(Project_LIB ${LIB_NAME})
set(Project_INCLUDE_DIRS ${LIB_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(Project_LIB ${Project_LIB} PARENT_SCOPE)
set(Project_INCLUDE_DIRS ${Project_INCLUDE_DIRS} PARENT_SCOPE)
