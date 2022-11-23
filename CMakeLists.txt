cmake_minimum_required(VERSION 3.14)

project(mutual_editing)

option(BUILD_TESTS "Build test programs" OFF)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -Wpedantic -Werror")

add_subdirectory("client_side")
add_subdirectory("server_side")

set(SERVER_LIB ${SERVER_LIB})
set(SERVER_INCLUDE_DIRS ${SERVER_INCLUDE_DIRS})

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(BUILD_TESTS)
