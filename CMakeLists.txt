cmake_minimum_required(VERSION 3.14)

project(mutual_editing)

option(BUILD_TESTS "Build test programs" ON)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -Wpedantic -Werror")

add_subdirectory("client_side")
add_subdirectory("server_side")

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(BUILD_TESTS)
